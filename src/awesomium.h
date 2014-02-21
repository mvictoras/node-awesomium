#ifndef AWESOMIUM_H
#define AWESOMIUM_H

#include <node.h>

#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>

#include <string>

using namespace Awesomium;

class WebBrowser : public node::ObjectWrap {
    
public:
    static void Init(v8::Handle<v8::Object> exports);

private:
    explicit WebBrowser(std::string url, int width, int height);
    ~WebBrowser();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
    static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
    //static void load(const v8::Arguments& args);
    void resize(int width, int height);
    void click(int x, int y);
   
    static v8::Persistent<v8::Function> constructor;

    static v8::Handle<v8::Value> getFrame(const v8::Arguments& args);
   
    char* base64_encode(const unsigned char *data,
                        size_t input_length,
                        size_t *output_length);
    
    void BGRAtoRGB(const unsigned char* bgra, int pixel_width, unsigned char* rgb);
    std::string convertToJpeg(const unsigned char* buffer);
  
  
    std::string mUrl;
    int mWidth;
    int mHeight;
    
    WebView* mView;
    WebCore* mWebCore;

    static const char encoding_table[];
    static const int mod_table[];

};

#endif
