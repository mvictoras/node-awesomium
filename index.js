var binding = require('./build/Release/awesomium')

var webBrowser = new binding.WebBrowser("http://hakim.se/experiments/html5/origami", 1366, 390);

module.exports.getFrame = function() {
    return webBrowser.getFrame();
}

module.exports.click = function(x, y) {
}

module.exports.hover = function(x, y) {
}

module.exports.resize = function(w, h) {
}
