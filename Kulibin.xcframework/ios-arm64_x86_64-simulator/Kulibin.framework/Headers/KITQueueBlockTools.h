//
//  Copyright (c) 2020 - present, LLC “V Kontakte”
//
//  1. Permission is hereby granted to any person obtaining a copy of this Software to
//  use the Software without charge.
//
//  2. Restrictions
//  You may not modify, merge, publish, distribute, sublicense, and/or sell copies, 
//  create derivative works based upon the Software or any part thereof.
//
//  3. Termination
//  This License is effective until terminated. LLC “V Kontakte” may terminate this
//  License at any time without any without any negative consequences to our rights.
//  You may terminate this License at any time by deleting the Software and all copies
//  thereof. Upon termination of this license for any reason, you shall continue to be
//  bound by the provisions of Section 2 above.
//  Termination will be without prejudice to any rights LLC “V Kontakte” may have as
//  a result of this agreement.
//
//  4. Disclaimer of warranty and liability
//  THE SOFTWARE IS MADE AVAILABLE ON THE “AS IS” BASIS. LLC “V KONTAKTE” DISCLAIMS
//  ALL WARRANTIES THAT THE SOFTWARE MAY BE SUITABLE OR UNSUITABLE FOR ANY SPECIFIC
//  PURPOSES OF USE. LLC “V KONTAKTE” CAN NOT GUARANTEE AND DOES NOT PROMISE ANY
//  SPECIFIC RESULTS OF USE OF THE SOFTWARE.
//  UNDER NO SIRCUMSTANCES LLC “V KONTAKTE” BEAR LIABILITY TO THE LICENSEE OR ANY
//  THIRD PARTIES FOR ANY DAMAGE IN CONNECTION WITH USE OF THE SOFTWARE.
//

#import <Foundation/Foundation.h>
#import <Kulibin/KITMacros.h>

NS_ASSUME_NONNULL_BEGIN

/// Create debounce block.
/// This function takes in a block, a time interval and a queue and returns another block. The returned block, after beging called, calls the one passed
/// as a parameter after ``timeInterval`` amount of time on ``queue``. Each successive call in specified period of time further delays the final call.
/// After ``timeInterval`` time passes without a call, ``block`` will be called only once.
/// @param timeInterval debounce interval. This must be greater than zero.
/// @param queue queue for ``block`` to be called on. If nil is passed, main queue will be used instead.
/// @param block operation to be executed
/// @return new block wrapping the original one and debouncing calls to it
/// @example ```
///     void (^searchBlock)(void) = KITDebounce(3.f, nil, ^{ [self performSearch]; })
///     self.textInput.onTextChanged = searchBlock; // kind of pseudocode
/// ```
KIT_EXPORT
KIT_OVERLOADABLE
NS_REFINED_FOR_SWIFT
void (^KITDebounceBlock(NSTimeInterval timeInterval, dispatch_queue_t _Nullable queue, void (^block)(void)))(void);

KIT_EXPORT
KIT_OVERLOADABLE
NS_REFINED_FOR_SWIFT
void (^KITDebounceBlock(NSTimeInterval timeInterval, dispatch_queue_t _Nullable queue, void (^block)(id _Nullable)))(id _Nullable);

KIT_EXPORT
NS_REFINED_FOR_SWIFT
void (^_KITDebounceBlock(NSTimeInterval timeInterval, dispatch_queue_t _Nullable queue, void (^block)(id _Nullable)))(id _Nullable);

/// Create a throttling block.
/// This function takes in a block, a time interval and a queue and returns another block. The returned block calls the one passed
/// as a parameter no more frequent than once per ``timeInterval``.
/// @param timeInterval throttle interval. This must be greater than zero.
/// @param queue queue for ``block`` to be called on. If nil is passed, main queue will be used instead.
/// @param block operation to be executed
/// @return new block wrapping the original one and debouncing calls to it
KIT_EXPORT
KIT_OVERLOADABLE
NS_REFINED_FOR_SWIFT
void (^KITThrottleBlock(NSTimeInterval timeInterval, dispatch_queue_t _Nullable queue, void (^block)(void)))(void);

KIT_EXPORT
KIT_OVERLOADABLE
NS_REFINED_FOR_SWIFT
void (^KITThrottleBlock(NSTimeInterval timeInterval, dispatch_queue_t _Nullable queue, void (^block)(id _Nullable)))(id _Nullable);

KIT_EXPORT
NS_REFINED_FOR_SWIFT
void (^_KITThrottleBlock(NSTimeInterval timeInterval, dispatch_queue_t _Nullable queue, void (^block)(id _Nullable)))(id _Nullable);

NS_ASSUME_NONNULL_END
