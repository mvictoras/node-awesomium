var binding = require('./build/Release/awesomium')

browsers = {}

var webBrowser;

module.exports.init = function(wallWidth, wallHeight, initWidth, initHeight) {
    webBrowser = new binding.WebBrowser(wallWidth, wallHeight, initWidth, initHeight);
}

module.exports.createWindow = function(id, url) {
    webBrowser.createWindow(id, url);
}

module.exports.removeWindow = function(id) {
    webBrowser.removeWindow(id);
}

module.exports.loadUrl = function(id, url) {
    webBrowser.loadUrl(id, url);
}

module.exports.getFrame = function(id) {
    return webBrowser.getFrame(id);
}

module.exports.click = function(id, x, y) {
    webBrowser.click(id, x, y);
}

module.exports.hover = function(x, y) {
}

module.exports.resize = function(id, w, h) {
    webBrowser.resize(id, w, h);
}
