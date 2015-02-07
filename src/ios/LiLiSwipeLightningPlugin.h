#import <Cordova/CDV.h>
#import	<ExternalAccessory/ExternalAccessory.h>
#import "LTDeviceDelegate.h"

@interface LiLiSwipeLightningPlugin : CDVPlugin <LTDeviceDelegate>
{
    CDVInvokedUrlCommand *listenerCommand;
}

- (BOOL) isConnected;

- (void)isConnected:(CDVInvokedUrlCommand*)command;

- (void)registerListener:(CDVInvokedUrlCommand*)command;


@end