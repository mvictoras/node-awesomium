#include "cefHandler.h"

#include <iostream>

//void ClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) {
//}

bool ClientHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) {

}
void ClientHandler::OnPaint(CefRefPtr<CefBrowser> browser,
                            PaintElementType type,
                            const RectList& dirtyRects,
                            const void* buffer,
                            int width,
                            int height) {
    std::cout << "Painting!" << std::endl;
}
