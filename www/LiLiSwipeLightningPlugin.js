/**
 * @author Daniel Boorn, daniel.boorn@gmail.com
 * @license CC BY-NC 4.0, http://creativecommons.org/licenses/by-nc/4.0/
 * @type {exports}
 */
var exec = require('cordova/exec');

var liliSwipeLightning = {
    start: function (resultHandler, errorHandler) {
        exec(function (result) {
            liliSwipeLightning.start(resultHandler, errorHandler);
            resultHandler(result);
        }, function (result) {
            liliSwipeLightning.start(resultHandler, errorHandler);
            errorHandler(result);
        }, "LiLiSwipeLightningPlugin", "registerListener", []);
    },
    isConnected: function (resultHandler, errorHandler) {
        exec(resultHandler, errorHandler, "LiLiSwipeLightningPlugin", "isConnected", []);
    }
};

module.exports = liliSwipeLightning;