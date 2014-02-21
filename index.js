var binding = require('./build/Release/awesomium')

browsers = {}

var webBrowser;

module.exports.load = function(id, url, width, height) {
    webBrowser = new binding.WebBrowser(id, url, width, height);
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
