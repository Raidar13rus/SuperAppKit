/*
Copyright (c) 2020 - present, LLC “V Kontakte”

1. Permission is hereby granted to any person obtaining a copy of this Software to
use the Software without charge.

2. Restrictions
You may not modify, merge, publish, distribute, sublicense, and/or sell copies, 
create derivative works based upon the Software or any part thereof.

3. Termination
This License is effective until terminated. LLC “V Kontakte” may terminate this
License at any time without any without any negative consequences to our rights.
You may terminate this License at any time by deleting the Software and all copies
thereof. Upon termination of this license for any reason, you shall continue to be
bound by the provisions of Section 2 above.
Termination will be without prejudice to any rights LLC “V Kontakte” may have as
a result of this agreement.

4. Disclaimer of warranty and liability
THE SOFTWARE IS MADE AVAILABLE ON THE “AS IS” BASIS. LLC “V KONTAKTE” DISCLAIMS
ALL WARRANTIES THAT THE SOFTWARE MAY BE SUITABLE OR UNSUITABLE FOR ANY SPECIFIC
PURPOSES OF USE. LLC “V KONTAKTE” CAN NOT GUARANTEE AND DOES NOT PROMISE ANY
SPECIFIC RESULTS OF USE OF THE SOFTWARE.
UNDER NO SIRCUMSTANCES LLC “V KONTAKTE” BEAR LIABILITY TO THE LICENSEE OR ANY
THIRD PARTIES FOR ANY DAMAGE IN CONNECTION WITH USE OF THE SOFTWARE.
*/

#import <Foundation/Foundation.h>

typedef NSTimer *(^TimerSetupBlock)(id, SEL);

@class KITTimerTarget;
@protocol KITTimerTargetDelegate <NSObject>
@required
- (void)timerTargetFired:(KITTimerTarget *)target;
@end

@interface KITTimerTarget : NSObject
@property (nonatomic, readwrite, weak) id<KITTimerTargetDelegate> delegate;

+ (KITTimerTarget *)timerTarget:(TimerSetupBlock)block;
+ (KITTimerTarget *)scheduledTimerTargetWithTimeInterval:(NSTimeInterval)timeInterval repeats:(BOOL)repeats;

- (void)invalidate;

@end

@interface NSTimer (KITBlocks)

+ (NSTimer *)timerWithTimeInterval:(NSTimeInterval)timeInterval repeats:(BOOL)repeats handler:(void (^)(NSTimer *))handler;

+ (NSTimer *)after:(NSTimeInterval)timeInterval handler:(void (^)(NSTimer *))handler;
+ (NSTimer *)every:(NSTimeInterval)timeInterval handler:(void (^)(NSTimer *))handler;

- (void)startInRunLoop:(NSRunLoop *)runLoop mode:(NSString *)mode;
- (void)start;

@end
