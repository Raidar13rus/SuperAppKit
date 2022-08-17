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

#import <Kulibin/KITMacros.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

NS_REFINED_FOR_SWIFT
typedef NS_ENUM(NSUInteger, KITPromiseState) {
    KITPromiseStateGiven,
    KITPromiseStateFulfilled,
    KITPromiseStateBroken
} KIT_ENUM_EXTENSIBILITY(closed);

KIT_FINAL_CLASS
NS_REFINED_FOR_SWIFT
@interface KITPromise<__covariant ObjectType> : NSObject<NSCopying>

/// Current state of the promise
- (id _Nullable)resultWithState:(out KITPromiseState *_Nullable)state;

/// Initializes promise that can be resolved later using resolver block
/// @param resolver block resolving promise with given value or error. Can only be called once.
- (instancetype)initResolvingWithBlock:(out void (^__strong _Nullable *_Nonnull)(_Nullable ObjectType, NSError *_Nullable))resolver NS_DESIGNATED_INITIALIZER KIT_NODISCARD;

/// Initialized an already resolved promise
/// @param result value or NSError object indicating error. Block values are not supported.
- (instancetype)initResolvedWithResult:(id _Nullable)result NS_DESIGNATED_INITIALIZER KIT_NODISCARD;

/// Attaches observer block to a promise
/// @param block block taking either value or error. Will only be called once
- (void)sink:(void (^)(ObjectType _Nullable result, NSError *_Nullable error))block;

/// Transforms
/// @param block a block returning either value, NSError object indicating error or another promise to continue upon
/// @returns promise that is resolved accroding to block's return value
- (KITPromise *)transform:(id _Nullable (^)(ObjectType _Nullable result, NSError *_Nullable error))block KIT_NODISCARD;

/// Transforms using provided dispatch strategy
/// @param block a block returning either value, NSError object indicating error or another promise to continue upon
/// @param dispatch a block used to dispatch actual work. May invoke it's argument on a separate queue or thread.
/// @returns promise that is resolved accroding to block's return value
- (KITPromise *)transform:(id _Nullable (^)(ObjectType _Nullable result, NSError *_Nullable error))block
                 dispatch:(void (^)(void (^)(void)))dispatch KIT_NODISCARD;

@end

NS_ASSUME_NONNULL_END
