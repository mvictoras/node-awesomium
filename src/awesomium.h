#ifndef AWESOMIUM_H
#define AWESOMIUM_H

#include <node.h>

#ifdef AWESOMIUM
#include <Awesomium/WebCore.h>
#include <Awesomium/BitmapSurface.h>
#include <Awesomium/STLHelpers.h>
#endif

#include "cefHandler.h"
#include "include/cef_client.h"

#include <map>
#include <string>

#define AWESOMIUM 0

#ifdef AWESOMIUM
using namespace Awesomium;
#endif

class WebBrowser : public node::ObjectWrap {

public:
    static void Init(v8::Handle<v8::Object> exports);

private:
    explicit WebBrowser(int wallWidth, int wallHeight, int initWidth, int initHeight);
    ~WebBrowser();

    static v8::Handle<v8::Value> New(const v8::Arguments& args);
    static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);
    static v8::Handle<v8::Value> PlusOne(const v8::Arguments& args);
    //static void load(const v8::Arguments& args);

    static v8::Persistent<v8::Function> constructor;

    static v8::Handle<v8::Value> getFrame(const v8::Arguments& args);
    static v8::Handle<v8::Value> createWindow(const v8::Arguments& args);
    static v8::Handle<v8::Value> removeWindow(const v8::Arguments& args);
    static v8::Handle<v8::Value> loadUrl(const v8::Arguments& args);
    static v8::Handle<v8::Value> resize(const v8::Arguments& args);
    static v8::Handle<v8::Value> click(const v8::Arguments& args);
    static v8::Handle<v8::Value> keyPress(const v8::Arguments& args);

    char* base64_encode(const unsigned char *data,
                        size_t input_length,
                        size_t *output_length);

    void BGRAtoRGB(const unsigned char* bgra, int pixel_width, unsigned char* rgb);
    std::string convertToJpeg(const unsigned char* buffer, int width, int height);


    std::string mUrl;
    int mWallWidth, mWallHeight, mInitWidth, mInitHeight;

    typedef std::map<std::string, int> StringToInt;
    StringToInt mViewWidth;
    StringToInt mViewHeight;

#ifdef AWESOMIUM
    typedef std::map<std::string, WebView*> WebViewType;
    WebViewType mViews;

    WebCore* mWebCore;
#else
    CefRefPtr<ClientHandler> clientHandler;
#endif

    static const char encoding_table[];
    static const int mod_table[];





};

#endif
