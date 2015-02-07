//
//  LTDeviceDelegate.h
//  LilitabDemo
//
//  Created on 4/20/12.
//  Copyright (c) 2012 Lilitab, LLC. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <ExternalAccessory/ExternalAccessory.h>
#import <ExternalAccessory/EAAccessory.h>

@protocol LTDeviceDelegate <NSObject>

@optional

- (void)accessoryWasConnected:(EAAccessory *)accessory;
- (void)accessoryWillDisconnect:(EAAccessory *)accessory;
- (void)accessoryWasDisconnected;

- (void) sessionOpenSuccessful:(EAAccessory *) accessory;
- (void) sessionOpenFailed:(EAAccessory *) accessory;

- (void)accessoryDidParseData:(NSDictionary *)parsedData;
- (void)accessoryDidFailParsingWithError:(NSError *)parseError;

// Added 5/15/12 for clients needing raw data that may not be
// US credit cards, e.g. insurance cards, driver's license, etc.
- (void)accessoryDidPassRawData:(NSString *)rawData;
- (void)accessoryDidPassRawDataOnly:(NSString *)rawData;

-(void)accessoryDidPassResponse:(NSString*)responseString  forCommand:(NSString*)commandName;

@end
