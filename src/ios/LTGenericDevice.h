//
//  LTDevice.h
//  LilitabDemo
//
//  Created on 4/20/12.
//  Copyright (c) 2012 Lilitab, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ExternalAccessory/ExternalAccessory.h>
#import <ExternalAccessory/EAAccessory.h>


#import "LTDeviceDelegate.h"

@interface LTGenericDevice : NSObject <EAAccessoryDelegate, NSStreamDelegate> {
    
    NSMutableString *_requestMessageName;
}

// BLOCKS

typedef void (^LTCompletionHandler) (NSString *);

@property (weak, nonatomic) id <LTDeviceDelegate> delegate;

// _accessory is the reference to the actual device inserted into the phne
@property (strong, nonatomic) EAAccessory *accessory;

// _session is the logical connection between the app and the device firmware after authentication
//@property (strong, nonatomic, readonly) NSString *protocolString;
@property (strong, nonatomic) NSString *protocolString;

// _protocolString is the user/GTL defined string to associate with the connection to the accessory
@property (strong, nonatomic) NSMutableString *completeCardReaderString;

@property (strong, nonatomic) NSMutableArray *accessoryList;
@property BOOL readerAttached;

//streams
@property (strong, nonatomic) EASession *session;
@property (strong, nonatomic) NSMutableData *writeData;

// For commanding MagTek
@property (strong, nonatomic) NSMutableString *requestMessageName;
@property BOOL forceResponseToHex;
@property (strong) LTCompletionHandler commandCompletionHanlder;

#pragma mark - Public Methods

- (id)initWithDelegate:(id <LTDeviceDelegate>)deviceDelegate;
// 6/3/12 - km - added to support user specified protocols
- (id)initWithDelegate:(id <LTDeviceDelegate>)deviceDelegate andProtocolString:(NSString *)protocol; 
- (void)tearDown;

- (void)_writeData;
- (void)_readData;

// 8/10/12 - Board Commands
-(void)resetLilitabSwipe;
//
//  You'll want to use these to reduce power consumption when
//  the iPad sleeps/wakes with the app in the foreground.
//
-(void)readerPowerOn;       // Used to turn reader power on when iPad wakes up with app running
                            // generally, you'll want to run this method when the applicationDidBecomeActive method fires.
-(void)readerPowerOff;      // User to turn reader power off when iPad goes to sleep up with app running
                            // generally, you'll want to run this method when the applicationWillResignActive method fires.

//
//  These are special power management functions that
//  will be implemented in a future release of the lilitab swipe
//  unit that will incorporate kiosk power management.
//
-(void)wakeWhenPowerDetectedOn;
-(void)wakeWhenPowerDetectedOff;

//reader commands

- (void)softwareIDWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)readerSerialWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)magneSafeVersionWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)trackIDEnabledWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)ISOMaskWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)RCVTimeoutWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)XmitTimeoutWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)DAVTimeoutWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)SPIModeWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)interfaceTypeWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)MagnePrintFlagsWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)sureSwipeFlagsWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)CRCFlagsWithCompletionHandler:(LTCompletionHandler)completionHandler;
- (void)decodeEnableWithCompletionHandler:(LTCompletionHandler)completionHandler;

//delegate commanding
- (void)sendCommandToReader:(unsigned char) cmd withName:(NSString*)cmdName;

@end
