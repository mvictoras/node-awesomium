var binding = require('./build/Release/awesomium')

browsers = {}

module.exports.load = function(url, width, height) {
    return new binding.WebBrowser(url, width, height);
}

module.exports.getFrame = function() {
    return webBrowser.getFrame();
}

module.exports.click = function(x, y) {
}

module.exports.hover = function(x, y) {
}

module.exports.resize = function(w, h) {
}
