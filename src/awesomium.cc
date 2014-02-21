#define BUILDING_NODE_EXTENSION
#include <node.h>
#include "awesomium.h"

#include <jpeglib.h>
#include <stdlib.h>

#if defined(__WIN32__) || defined(_WIN32)
    #include <windows.h>
    #define sleep(x) Sleep(x)
#elif defined(__APPLE__) || defined(__linux__)
    #include <unistd.h>
    #define sleep(x) usleep(x * 1000)
#endif

#define SLEEP_MS 50

using namespace v8;

Persistent<Function> WebBrowser::constructor;

const char WebBrowser::encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                     'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                     'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                     'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                     'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                     'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                     'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                     '4', '5', '6', '7', '8', '9', '+', '/'};
const int WebBrowser::mod_table[] = {0, 2, 1};


WebBrowser::WebBrowser(std::string url, int width, int height) : 
    mUrl(url), mWidth(width), mHeight(height) {

        WebConfig conf;
        conf.log_level = kLogLevel_Verbose;
                  
        mWebCore = WebCore::Initialize(conf);
        //mView = mWebCore->CreateWebView(1981, 1081, 0, kWebViewType_Offscreen);
        mView = mWebCore->CreateWebView(width, height, 0, kWebViewType_Offscreen);
                                              
        // XXXXX
        WebURL webUrl(WSLit(url.c_str()));
        mView->LoadURL(webUrl);
    
        while(mView->IsLoading()) {
            sleep(SLEEP_MS);
            // required
            mWebCore->Update();
        }
}

WebBrowser::~WebBrowser() {
}

void WebBrowser::Init(Handle<Object> exports) {
    // Prepare constructor template
    Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
    tpl->SetClassName(String::NewSymbol("WebBrowser"));
    tpl->InstanceTemplate()->SetInternalFieldCount(3);
    // Prototype
    tpl->PrototypeTemplate()->Set(String::NewSymbol("plusOne"),
        FunctionTemplate::New(PlusOne)->GetFunction());
    tpl->PrototypeTemplate()->Set(String::NewSymbol("getFrame"),
        FunctionTemplate::New(getFrame)->GetFunction());
    constructor = Persistent<Function>::New(tpl->GetFunction());
    exports->Set(String::NewSymbol("WebBrowser"), constructor);
}

Handle<Value> WebBrowser::New(const Arguments& args) {

    if (args.IsConstructCall()) {
        // Invoked as constructor: `new WebBrowser(...)`
        String::Utf8Value url(args[0]->ToString());
        //String::Utf8Value sWidth(args[1]->ToString());
        //int width = atoi(std::string(*sWidth).c_str());
        //int height = (int) args[2]->Int32Value();
        const uint32_t width = args[1]->Uint32Value();
        //int width = 1366;
        int height = 390;

        //WebBrowser* obj = new WebBrowser(std::string(*url), width, height);
        WebBrowser* obj = new WebBrowser(std::string(*url), width, 390);
        obj->Wrap(args.This());
        return args.This();
    } else {
        // Invoked as plain function `WebBrowser(...)`, turn into construct call.
        HandleScope scope;
        const int argc = 3;
        Local<Value> argv[argc] = { args[0], argv[1], argv[2] };
        return scope.Close(constructor->NewInstance(argc, argv));
    }
}

Handle<Value> WebBrowser::PlusOne(const Arguments& args) {
    HandleScope scope;

    //WebBrowser* obj = ObjectWrap::Unwrap<WebBrowser>(args.This());
    //obj->value_ += 1;

    return scope.Close(Number::New(10));
}    

Handle<v8::Value> WebBrowser::getFrame(const Arguments& args) {
    HandleScope scope;

    WebBrowser* obj = ObjectWrap::Unwrap<WebBrowser>(args.This());
    obj->mWebCore->Update();
    
    BitmapSurface* surface = (BitmapSurface*)obj->mView->surface();
    
    if (surface != 0) {
        return scope.Close(String::New(obj->convertToJpeg(surface->buffer()).c_str()));
    } else {
    }

    return scope.Close(String::New(""));
}

void WebBrowser::resize(int width, int height) {
    mWidth = width;
    mHeight = height;
    mView->Resize(width, height);
}

void WebBrowser::click(int x, int y) {
    mView->InjectMouseMove(x, y);
    mView->InjectMouseDown(kMouseButton_Left);
    mView->InjectMouseUp(kMouseButton_Left);
}

char* WebBrowser::base64_encode(const unsigned char *data,
                                size_t input_length,
                                size_t *output_length) {

    *output_length = 4 * ((input_length + 2) / 3);

    char *encoded_data = (char*)malloc(sizeof(char*) * *output_length);
    if (encoded_data == NULL) return NULL;

    for (unsigned int i = 0, j = 0; i < input_length;) {

        uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
        uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[*output_length - 1 - i] = '=';

    return encoded_data;
}

/* Converts a line from BGRA to RGB */
void WebBrowser::BGRAtoRGB(const unsigned char* bgra, int pixel_width, unsigned char* rgb) {
    for (int x = 0; x < pixel_width; x++) {
        const unsigned char* pixel_in = &bgra[x * 4];
        unsigned char* pixel_out = &rgb[x * 3];
        pixel_out[0] = pixel_in[2];
        pixel_out[1] = pixel_in[1];
        pixel_out[2] = pixel_in[0];
    }
}

std::string WebBrowser::convertToJpeg(const unsigned char* buffer) {
    unsigned char* rgb = (unsigned char*) malloc(sizeof(unsigned char*) * mWidth);

    jpeg_compress_struct cinfo;
    jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jerr.trace_level = 10;
    
    jpeg_create_compress(&cinfo);
    //boost::uint8_t *jpeg_buffer_raw = NULL;
    unsigned char *jpeg_buffer_raw = NULL;
    unsigned long outbuffer_size = 0;
    jpeg_mem_dest(&cinfo, &jpeg_buffer_raw, &outbuffer_size);

    cinfo.image_width = mWidth;
    cinfo.image_height = mHeight;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;
    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, 100, true);
    jpeg_start_compress(&cinfo, true);
    int row_stride = mWidth * 4;
    JSAMPROW row_pointer[1];
    
    while (cinfo.next_scanline < cinfo.image_height) {
        BGRAtoRGB(&buffer[cinfo.next_scanline * row_stride], mWidth, rgb);
        row_pointer[0] = (JSAMPROW) rgb;
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    
    size_t out;
    char* base64 = base64_encode(jpeg_buffer_raw, outbuffer_size, &out);

    std::string sBuffer(base64, base64 + out);

    free(rgb);
    free(base64);

    return sBuffer;
}
