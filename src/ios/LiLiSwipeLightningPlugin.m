#import "LiLiSwipeLightningPlugin.h"
#import <Cordova/CDV.h>
#import "LiliswipeSDK.h"

@interface LiLiSwipeLightningPlugin ()

//@property (strong, nonatomic) LTMagTekReader *cardReader;

@end

@implementation LiLiSwipeLightningPlugin

//@synthesize cardReader = _cardReader;

int lililopendev=0;

- (void)pluginInitialize;
{
    NSLog(@"In LiLiSwipeLightningPlugin Init");

    //    _cardReader = [[LTMagTekReader alloc] initWithDelegate:self andProtocolString:@"com.lilitab.p1"];
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(accessoryDidConnect:) name:Liliswipe_DidConnectNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(accessoryDidDisconnect:) name:Liliswipe_DidDisconnectNotification object:nil];
    [Liliswipe sharedSwipe].enableAttachmentNotification = YES;

    
    [super pluginInitialize];
}

- (void)accessoryDidConnect:(NSNotification*)notification {
    NSLog(@"LiLiSwipe Connected");
    [Liliswipe sharedSwipe].ledState = LED_On;
    [Liliswipe sharedSwipe].enableSwipe = YES;
    [Liliswipe sharedSwipe].swipeTimeout = 1000000000000000000;
    [Liliswipe sharedSwipe].swipeBlock = ^(NSDictionary* swipeData)
    {
        [self receiveSwipe:swipeData];
    };
    
    lililopendev=1;
    
    if(listenerCommand){
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Connected"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:listenerCommand.callbackId];
    }
    
}

- (void)accessoryDidDisconnect:(NSNotification*)notification {
    
    NSLog(@"LiLiSwipe Disconnected");
    [Liliswipe sharedSwipe].enableSwipe = NO;
    [Liliswipe sharedSwipe].swipeBlock = NULL;
    if(lililopendev && listenerCommand){
        CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:@"Disconnected"];
        [self.commandDelegate sendPluginResult:pluginResult callbackId:listenerCommand.callbackId];
    }
    lililopendev=0;
    
}


- (void) receiveSwipe:(NSDictionary*)swipeData   {
    
    NSLog(@"LiLiSwipe Accessory Data Notification Received");
    
    NSString* output;
    NSString* status = [swipeData objectForKey:@"status"];
    
    if( [status isEqualToString:@"timeout"] )
    {
        NSLog(@"Swipe timed out");
    }else{
        NSString* track1 = [swipeData objectForKey:@"Track1"];
        NSString* track2 = [swipeData objectForKey:@"Track2"];
        NSString* track3 = [swipeData objectForKey:@"Track3"];
        output = [NSString stringWithFormat:@"Track1: %@\rTrack2: %@\rTrack3: %@\r",track1,track2,track3];
        
        if(listenerCommand){
            NSLog(@"%@", listenerCommand.callbackId);
            NSLog(@"Sending plugin data notification");
            NSLog(@"Sending response:%@", track1);
            CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:track1];
            [self.commandDelegate sendPluginResult:pluginResult callbackId:listenerCommand.callbackId];
        }
        
    }
    
    [Liliswipe sharedSwipe].ledState = LED_On;
    [Liliswipe sharedSwipe].enableSwipe = YES;

}


- (BOOL) isConnected
{
    return lililopendev;
}

- (void)isConnected:(CDVInvokedUrlCommand *)command
{
    NSLog(@"isConnected");
    CDVPluginResult* pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsBool:[self isConnected]];
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void)registerListener:(CDVInvokedUrlCommand*)command
{
    NSLog(@"Registering Cordova JS Listener");
    listenerCommand = command;
}


@end