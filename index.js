var binding = require('./build/Release/awesomium')

var webBrowser = binding.MyObject(10);

module.exports.plusOne = function() {
    return webBrowser.plusOne();
}
