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

#import <Kulibin/Kulibin.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface KITPromise<ObjectType> (Dispatch)

/// Creates a promise that is resolved by running a block synchronously
/// @param queue dispatch queue to run block on
/// @param block block accepting resolver
+ (instancetype)syncOnQueue:(dispatch_queue_t)queue give:(void (^)(void (^resolve)(id _Nullable, NSError *_Nullable)))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously
/// @param queue dispatch queue to run block on
/// @param block block accepting resolver
+ (instancetype)asyncOnQueue:(dispatch_queue_t)queue give:(void (^)(void (^resolve)(id _Nullable, NSError *_Nullable)))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously after a certain delay
/// @param queue dispatch queue to run block on
/// @param delay delay in seconds before block will be ran
/// @param block block accepting resolver
+ (instancetype)asyncOnQueue:(dispatch_queue_t)queue
                  afterDelay:(NSTimeInterval)delay
                        give:(void (^)(void (^resolve)(id _Nullable, NSError *_Nullable)))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously after a certain point in time
/// @param queue dispatch queue to run block on
/// @param time time after which block will be ran
/// @param block block accepting resolver
+ (instancetype)asyncOnQueue:(dispatch_queue_t)queue
                       after:(dispatch_time_t)time
                        give:(void (^)(void (^resolve)(id _Nullable, NSError *_Nullable)))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously
/// @param queue dispatch queue to run block on
/// @param block block returning value or NSError object indicating error or next promise to continue upon
+ (instancetype)syncOnQueue:(dispatch_queue_t)queue do:(id _Nullable (^)(void))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously
/// @param queue dispatch queue to run block on
/// @param block block returning value or NSError object indicating error or next promise to continue upon
+ (instancetype)asyncOnQueue:(dispatch_queue_t)queue do:(id _Nullable (^)(void))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously after a certain delay
/// @param queue dispatch queue to run block on
/// @param delay delay in seconds before block will be ran
/// @param block block returning value or NSError object indicating error or next promise to continue upon
+ (instancetype)asyncOnQueue:(dispatch_queue_t)queue
                  afterDelay:(NSTimeInterval)delay
                          do:(id _Nullable (^)(void))block KIT_NODISCARD;

/// Creates a promise that is resolved by running a block asynchronously after a certain point in time
/// @param queue dispatch queue to run block on
/// @param time time after which block will be ran
/// @param block block returning value or NSError object indicating error or next promise to continue upon
+ (instancetype)asyncOnQueue:(dispatch_queue_t)queue
                       after:(dispatch_time_t)time
                          do:(id _Nullable (^)(void))block KIT_NODISCARD;

/// Transforms
/// @param queue dispatch queue to run block on asynchronously
/// @param block a block returning either value, NSError object indicating error or another promise to continue upon
/// @returns promise that is resolved accroding to block's return value
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue transform:(id _Nullable (^)(ObjectType _Nullable result, NSError *_Nullable error))block KIT_NODISCARD;

/// Transform promise's value
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and returning new value
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue map:(id (^)(ObjectType _Nullable, NSError *_Nullable error))block;

/// Transform promise using its value
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and returning next promise to continue upon
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue flatMap:(KITPromise *(^)(ObjectType _Nullable, NSError *_Nullable error))block;

/// Access promise's value without modifying it
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value
- (KITPromise<ObjectType> *)asyncOnQueue:(dispatch_queue_t)queue tapValue:(void (^)(id _Nullable))block;

/// Transform promise's value
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and returning new value
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue mapValue:(id (^)(ObjectType _Nullable))block;

/// Transform promise using its value
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and returning next promise to continue upon
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue flatMapValue:(KITPromise *(^)(ObjectType _Nullable))block;

/// Access promise's value without modifying it
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and error
- (KITPromise<ObjectType> *)asyncOnQueue:(dispatch_queue_t)queue tap:(void (^)(id _Nullable, NSError * _Nullable))block;

/// Access promise's error without modifying it
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value
- (KITPromise<ObjectType> *)asyncOnQueue:(dispatch_queue_t)queue tapError:(void (^)(NSError * _Nullable))block;

/// Transform promise's value
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and returning new value
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue mapError:(id (^)(NSError *))block;

/// Transform promise using its value
/// @param queue dispatch queue to run block on asynchronously
/// @param block block accepting value and returning next promise to continue upon
- (KITPromise *)asyncOnQueue:(dispatch_queue_t)queue flatMapError:(KITPromise *(^)(NSError *))block;

/// Blocks current thread until the promise is resolved
- (id _Nullable)blockAndWait;

/// Blocks but continues to spin the runloop until the promise is resolved
/// @warning Do not use this. No, seriously, don't.
- (id _Nullable)await;

@end

NS_ASSUME_NONNULL_END
