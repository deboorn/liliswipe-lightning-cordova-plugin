# LiLiSwipe  Cordova Plugin

LiLiSwipe Cordova Plugin for use with LiLiSwipe Mobile Lightning Reader for iOS. It's recommended that you 1st test your device using the LiLiSwipe SDK demos provided by LiLiTab.

More Info on LiLiSwipe Reader: <br>
http://www.lilitab.com/products/liliswipe-magnetic-stripe-reader


### License

CC BY 4.0 http://creativecommons.org/licenses/by/4.0/<br>
Core LiLiSwipe iOS SDK files are Copyright of their Respective Owners.

### Installation & Usage

Installation Step 1: Add Plugin to App Project
```
$ cordova plugin add https://github.com/deboorn/liliswipe-lightning-cordova-plugin
```
Step 2: Add a plugin definition to the `config.xml`
```
<feature name="LiLiSwipeLightningPlugin">
    <param name="ios-plugin" value="LiLiSwipeLightningPlugin" />
</feature>
```

Step 3: Invoke plugin from HTML
```
//place in your application js, document must be loaded prior to invoking
  liliSwipe.start(function(result){
      alert(result);
  }, function(error){
      alert("Error: " + error);
  });
```

The 1st param is the result handler followed by the error handler. LiLiSwipe events will be sent to the result handler.
Events include:
- "Connected" - For notification of LiLiSwipe reconnection only.
- "Disconnected" - For notification of LiLiSwipe disconnection.
- OR, card data, where card data is from a swipe

Step4: Add iOS Platform & Build
```
$ cordova platform add ios
$ cordova build ios
```

What's Next?<br>
- Open the project in XCode and run on device.
- Refactor the resultHander and errorHander in Step 3.

LiLiSwipeLightningPlugin Methods:
- `liliSwipe.start(resultHandler, errorHandler)` - Get disconnect, connect and swipe events.
- `liliSwipe.isConnected(resultHandler, errorHandler)` - Get current device status of LiLiSwipe device.