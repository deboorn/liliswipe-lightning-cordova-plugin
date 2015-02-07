//
//  Liliswipe.h
//  LiliTest
//
//  Created by Kevin Snow on 6/28/14.
//  Copyright (c) 2014 Lilitab. All rights reserved.
//

#import <Foundation/Foundation.h>

    // App needs to:
    //      set "Other Linker Flags to -ObjC
    //      add path to header to library search path


    // LED states
typedef NS_ENUM(NSInteger, Liliswipe_LED_Mode)
{
    LED_Off,
    LED_On,
    LED_Blink1,
    LED_Blink2,
    LED_Blink3,
    LED_Blink4,
    LED_SwipeForward,
    LED_SwipeReverse
};


    // Names used with NSNotificationCenter to be notified of connect/disconnect events
#define     Liliswipe_DidConnectNotification        @"Liliswipe_DidConnectNotification"
#define     Liliswipe_DidDisconnectNotification     @"Liliswipe_DidDisconnectNotification"

#define     Liliswipe_Version       @"1.0b4"


@interface Liliswipe : NSObject


    /////////////////////////////////////////////////////////////////////
    // shareSwipe - Singleton object for communication with liliswipe
    //
+(Liliswipe*) sharedSwipe;


    /////////////////////////////////////////////////////////////////////
    // isAttached - readonly property containing presence of liliswipe
    //
@property (nonatomic,readonly)  BOOL                isAttached;


    /////////////////////////////////////////////////////////////////////
    // status - The completionBLock is executed after the status information
    // has been read from the swipe.
    //
-(void) status:(void (^)(BOOL success,NSDictionary* results))completionBlock;


    /////////////////////////////////////////////////////////////////////
    // ledState - Controls the LEDs on the swipe. Defaults to LED_Off.
    //
@property (nonatomic,assign)    Liliswipe_LED_Mode  ledState;


    /////////////////////////////////////////////////////////////////////
    // setHeadTimeTo - Time passed to the card reader head.
    //
-(void) setHeadTimeTo:(NSDate*)date;


    /////////////////////////////////////////////////////////////////////
    // noPowerBlinkDuration - Controls the duration between blinks on the
    // if not power is present. Defaults to 0 (no blink)
    //
@property (nonatomic,assign)    NSTimeInterval      noPowerBlinkDuration;


    /////////////////////////////////////////////////////////////////////
    // Swiping - Set the block property to the block to execute when a swipe
    // happens. Use the enable property to enable/disable callbacks.
    // After enabling swipe, it stays active until a swipe or timeout.
    // A timeout of 0 is infinite 
@property (nonatomic,copy)                    void(^swipeBlock)(NSDictionary* swipeData);
@property (nonatomic,assign)    BOOL                enableSwipe;            // default: NO
@property (nonatomic,assign)    BOOL                allowMultipleSwipes;    // default: NO
@property (nonatomic,assign)    NSTimeInterval      swipeTimeout;


    /////////////////////////////////////////////////////////////////////
    // Firmware
    //
-(void) updateFirmware:(NSData*)firmware
                withProgress:(void (^)(float percent0to1))progressBlock
                withCompletion:(void (^)(BOOL success))completionBlock;

-(void) cancelFirmwareUpdate;

    /////////////////////////////////////////////////////////////////////
    // enableAttachmentNotification - After adding NSNotification observers to
    // Liliswipe_DidConnectNotification & Liliswipe_DidDisconnectNotification this is
    // called to generate notifications.
    //
@property (nonatomic,assign)    BOOL                enableAttachmentNotification;


    /////////////////////////////////////////////////////////////////////
    // enableLogging - Have library generate NSLog console messages.
    // debugMessages - Have library pass debug strings to app.
    // version - return a version string of the library
    //
    // Used for SDK development/testing
    //
@property (nonatomic,assign)    BOOL                enableLogging;
@property (nonatomic,copy)                      void(^debugMessages)(NSString* msg);

@property (nonatomic,readonly)  NSString*           version;

    /////////////////////////////////////////////////////////////////////
@end



