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

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(Queue.Priority)
typedef NS_ENUM(NSInteger, KITQueuePriority) {
    KITQueuePriorityLowBackground   = -8L,
    KITQueuePriorityLow             = -4L,
    KITQueuePriorityNormal          = 0,
    KITQueuePriorityHigh            = 4,
    KITQueuePriorityHighInteractive = 8
};

NS_SWIFT_NAME(Queue)
@interface KITQueue : NSObject

@property (class, atomic, readonly, strong) KITQueue *main;
@property (class, atomic, readonly, strong) KITQueue *concurrent;
@property (class, atomic, readonly, strong) KITQueue *concurrentBackground;

+ (KITQueue *)concurrentWithPriority:(KITQueuePriority)priority;
+ (KITQueue *)serialWithPriority:(KITQueuePriority)priority;
+ (KITQueue *)nativeQueue:(dispatch_queue_t)nativeQueue;

- (instancetype)init;
- (instancetype)initWithName:(NSString *)name;
- (instancetype)initWithPriority:(KITQueuePriority)priority;
- (instancetype)initWithPriority:(KITQueuePriority)priority concurrent:(BOOL)concurrent;
- (instancetype)initWithPriority:(KITQueuePriority)priority name:(nullable NSString *)name;
- (instancetype)initWithPriority:(KITQueuePriority)priority name:(nullable NSString *)name concurrent:(BOOL)concurrent;

- (instancetype)initWithNativeQueue:(dispatch_queue_t)queue;

- (void)dispatch:(dispatch_block_t)block;
- (void)dispatch:(dispatch_block_t)block synchronous:(BOOL)synchronous;
- (void)dispatchAfter:(NSTimeInterval)seconds block:(dispatch_block_t)block;
- (void)dispatchAsync:(dispatch_block_t)block;
- (void)dispatchSync:(dispatch_block_t)block;

- (BOOL)isCurrentQueue;
- (dispatch_queue_t _Nullable)nativeQueue;

@end

@interface NSThread (Kulibin)

- (void)dispatchBlock:(dispatch_block_t)block;
- (void)dispatchBlock:(dispatch_block_t)block waitUntilDone:(BOOL)waitUntilDone;
- (void)dispatchAfter:(NSTimeInterval)seconds block:(dispatch_block_t)block;

+ (void)dispatchBlockInBackground:(dispatch_block_t)block;
+ (void)executeBlock:(dispatch_block_t)block;

@end

NS_ASSUME_NONNULL_END
