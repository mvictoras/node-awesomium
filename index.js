var binding = require('./build/Release/awesomium')

var webBrowser = binding.WebBrowser("http://www.vimeo.com", '1366', 390);

module.exports.getFrame = function() {
    return webBrowser.getFrame();
}

module.exports.click = function(x, y) {
}

module.exports.hover = function(x, y) {
}

module.exports.resize = function(w, h) {
}
