#include "cefHandler.h"

OSRHandler::OSRHandler(int width, int height) {
    renderWidth = width;
    renderHeight = height;
}

void OSRHandler::setRenderSize(int width, int height) {
    renderWidth = width;
    renderHeight = height;
}

bool OSRHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect) {
    rect = CefRect(0, 0, renderWidth, renderHeight);
    return true;
}

void OSRHandler::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height) {
    unsigned char* img = (unsigned char*)buffer;
    printf("frame rendered (pixel[0]: (%d %d %d - %d)\n", img[2], img[1], img[0], img[3]);
}

BrowserClient::BrowserClient(OSRHandler *renderHandler) {
    m_renderHandler = renderHandler;
}

CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() {
    return m_renderHandler;
}

