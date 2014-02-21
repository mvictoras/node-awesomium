var binding = require('./build/Release/awesomium')

browsers = {}

var webBrowser;

module.exports.init = function(wallWidth, wallHeight, initWidth, initHeight) {
    webBrowser = new binding.WebBrowser(wallWidth, wallHeight, initWidth, initHeight);
}

module.exports.createWindow = function(id, url) {
    webBrowser.createWindow(id, url);
}

module.exports.loadUrl = function(id, url) {
    webBrowser.loadUrl(id, url);
}

module.exports.getFrame = function(id) {
    return webBrowser.getFrame(id);
}

module.exports.click = function(x, y) {
}

module.exports.hover = function(x, y) {
}

module.exports.resize = function(w, h) {
}
