#ifndef CEF_HANDLER_H_
#define CEF_HANDLER_H_
#pragma once

#include "include/cef_client.h"
/*
class ClientHandler : public CefClient,
                      public CefLifeSpanHandler,
                      public CefRenderHandler {

    public:
        class RenderHandler : public CefRenderHandler {
            public:
                virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) =0;
        };

    // CefRenderHandler methods
    virtual bool GetViewRect(CefRefPtr<CefBrowser> browser,
            CefRect& rect) OVERRIDE;

    virtual void OnPaint(CefRefPtr<CefBrowser> browser,
                         PaintElementType type,
                         const RectList& dirtyRects,
                         const void* buffer,
                         int width,
                         int height) OVERRIDE;

    CefRefPtr<CefBrowser> GetBrowser() { return m_Browser; }

protected:
    CefRefPtr<CefBrowser> m_Browser;
    static int m_BrowserCount;

public:
    IMPLEMENT_REFCOUNTING(ClientHandler);
    // Include the default locking implementation.
    IMPLEMENT_LOCKING(ClientHandler);
}; */

class OSRHandler : public CefRenderHandler {
private:
    int renderWidth;
    int renderHeight;
    int frames;

public:
    OSRHandler(int width, int height);

    void setRenderSize(int width, int height);

    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height);

    IMPLEMENT_REFCOUNTING(OSRHandler);
};

class BrowserClient : public CefClient {
private:
    CefRefPtr<CefRenderHandler> m_renderHandler;

public:
    BrowserClient(OSRHandler *renderHandler);

    virtual CefRefPtr<CefRenderHandler> GetRenderHandler();

    IMPLEMENT_REFCOUNTING(BrowserClient);
};
#endif
