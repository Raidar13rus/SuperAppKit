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

#import <Kulibin/KITPromise.h>

NS_ASSUME_NONNULL_BEGIN

@interface KITPromise<ObjectType>(ExtraInitialization)

/// Creates promise that can be resolved later using resolver block
/// @param resolver block resolving promise with given value or error. Can only be called once.
+ (instancetype)promiseResolvingWithBlock:(out void (^__strong _Nullable *_Nonnull)(_Nullable ObjectType, NSError *_Nullable))resolver KIT_NODISCARD;

/// Creates an already resolved promise
/// @param result value or NSError object indicating error. Block values are not supported.
+ (instancetype)promiseResolvedWithResult:(id _Nullable)result KIT_NODISCARD;

/// Creates an already fulfilled promise
/// @param value value for promise to hold. Block values are not supported.
+ (instancetype)promiseFulfilledWithValue:(_Nullable ObjectType)value KIT_NODISCARD;

/// Creates an already broken promise
/// @param error error for promise to hold. Can not be nil.
+ (instancetype)promiseBrokenWithError:(NSError *)error KIT_NODISCARD;

/// Initialized an already fulfilled promise
/// @param value value for promise to hold. Block values are not supported.
- (instancetype)initFulfilledWithValue:(_Nullable ObjectType)value KIT_NODISCARD;

/// Initialized an already broken promise
/// @param error error for promise to hold. Can not be nil.
- (instancetype)initBrokenWithError:(NSError *)error KIT_NODISCARD;

/// Creates a promise by passing resolver block to a passed block
/// @param block block that will be launched with resolved block as it's parameter
/// @note this method simply wraps `+[KITPromise promiseResolvingWithBlock:]` for convenience
+ (instancetype)give:(void (^NS_NOESCAPE)(void (^resolve)(ObjectType _Nullable, NSError *_Nullable)))block KIT_NODISCARD;
/// Initializes a promise by passing resolver block to a passed block
/// @param block block that will be launched with resolved block as it's parameter
/// @note this method simply wraps `-[KITPromise initResolvingWithBlock:]` for convenience
- (instancetype)initGiving:(void (^NS_NOESCAPE)(void (^resolve)(ObjectType _Nullable, NSError *_Nullable)))block KIT_NODISCARD;


/// Creates a promise that is resolved accoring to block's return value
/// @param block block returning result (value or error) or next promise to continue upon
/// @note this method is semantically equivalient to `[[KITPromise new] transform:block]`
+ (instancetype)do:(id (^NS_NOESCAPE)(void))block KIT_NODISCARD;

/// Initializes a promise that is resolved accoring to block's return value
/// @param block block returning result (value or error) or next promise to continue upon
/// @note this method is semantically equivalient to `[[KITPromise new] transform:block]`
- (instancetype)initDoing:(id (^NS_NOESCAPE)(void))block KIT_NODISCARD;

@end

@interface KITPromise<ObjectType>(ExtraOperators)

/// Access promise's value without modifying it
/// @param block block accepting value and error
- (KITPromise<ObjectType> *)tap:(void (^)(ObjectType _Nullable, NSError * _Nullable))block;
/// Transform promise's value
/// @param block block accepting value and error, and returning new value
- (KITPromise *)map:(id (^)(ObjectType _Nullable, NSError * _Nullable))block;
/// Transform promise using its value
/// @param block block accepting value and error, and returning next promise to continue upon
- (KITPromise *)flatMap:(KITPromise *(^)(ObjectType _Nullable, NSError * _Nullable))block;

/// Access promise value without modifying it
/// @param block block accepting value
- (KITPromise<ObjectType> *)tapValue:(void (^)(ObjectType _Nullable))block;
/// Transform promise using its value into new promise with result returned by block
/// @param block block accepting value and returning new value
- (KITPromise *)mapValue:(id (^)(ObjectType _Nullable))block;
/// Transform promise using its value into new promise
/// @param block block accepting value and returning next promise to continue upon
- (KITPromise *)flatMapValue:(KITPromise *(^)(ObjectType _Nullable))block;

/// Access promise error without modifying it
/// @param block block accepting value
- (KITPromise<ObjectType> *)tapError:(void (^)(NSError *_Nullable))block;
/// Transform promise using its error into new promise with result returned by block
/// @param block block accepting error and returning new result or error
/// @note this method can be used to recover from error
- (KITPromise<ObjectType> *)mapError:(id (^)(NSError *))block;
/// Transform promise using its error into new promise
/// @param block block accepting error and returning next promise to continue upon
/// @note this method can be used to recover from error
- (KITPromise *)flatMapError:(KITPromise *(^)(NSError *))block;

@end

@interface KITPromise<ObjectType>(ExtraOperations)

/// Reduces array of promises into a single value
/// @param inPromises array of promises to be reduced
/// @param acc initial value passed to the reducer
/// @param block reducer block, taking an accumulator value and result and returning next accumulator value
+ (KITPromise *)reduceArray:(NSArray<KITPromise *> *)inPromises
               startingFrom:(id)acc
                 usingBlock:(id (^)(id, id _Nullable, NSError *_Nullable))block;

/// Reduces array of promises into a single value
/// @param inPromises array of promises to be reduced
/// @param acc accumulator value passed to the reducer
/// @param block retududer block taking result and modifying accumulator value
+ (KITPromise *)reduceArray:(NSArray<KITPromise *> *)inPromises
                       into:(id)acc
                 usingBlock:(void (^)(id __strong _Nonnull *_Nonnull, id _Nullable, NSError *_Nullable))block;

/// Creates promise that is fulfilled with values of all promises or broken with the first error occured
/// @param inPromises promises, null-terminated
+ (KITPromise<NSArray<ObjectType> *> *)allOf:(KITPromise *)inPromises, ... NS_REQUIRES_NIL_TERMINATION;
/// Creates promise that is fulfilled with values of all promises in an array or broken with the first error occured
/// @param inPromises array of promises
+ (KITPromise<NSArray<ObjectType> *> *)allInArray:(NSArray<KITPromise *> *)inPromises;

/// Creates promise that is fulfilled with the first value available or broken with the last error occured
/// @param inPromises promises, null-terminated
+ (KITPromise<ObjectType> *)anyOf:(KITPromise *)inPromises, ... NS_REQUIRES_NIL_TERMINATION;
/// Creates promise that is fulfilled with the first value available or broken with the last error occured
/// @param inPromises array of promises
+ (KITPromise<ObjectType> *)anyInArray:(NSArray<KITPromise *> *)inPromises;

@end

NS_ASSUME_NONNULL_END
