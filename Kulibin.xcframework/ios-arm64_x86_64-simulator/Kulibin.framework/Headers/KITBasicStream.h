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
#import "KITMacros.h"

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString *KITStringForStreamStatus(NSStreamStatus status);
FOUNDATION_EXPORT BOOL KITStreamStatusIsReady(NSStreamStatus status);

#pragma mark - <KITBasicStreamPosing>

/// Protocol used to denote streams viable to be used as imposed identity by KITBasicStream
@protocol KITBasicStreamPosing <NSStreamDelegate>

/// Abstract method called by parent's open implementation
/// @param error Output error. If NO is returned, stream automatically transitioned to AtError state and
///     this error beomes streamError
- (BOOL)p_openWithError:(out NSError *__autoreleasing *)error;

/// Abstract method called by parent's close implementation
/// @param error Output error. If NO is returned, stream automatically transitioned to AtError state and
///     this error beomes streamError
- (BOOL)p_closeWithError:(out NSError *__autoreleasing *)error;

@end

#pragma mark - KITBasicStream

/// Base class simplifying creation of custom streams.
/// @discussion Normally one would need to implement everything in NSStream's interface to create their own stream.
/// KITBasicStream lifts that burden from you: it automatically manages stream state, runloop scheduling, handles errors erc.
/// For subclassing NSInputStream or NSOutputStream see KITBasicInputStream and KITBasicOutputStream respectively
@interface KITBasicStream: NSStream<KITBasicStreamPosing>

/// Stream delegate object
/// @discussion By default stream is its own delegate. Setting nil to this property resets it to self or imposed identity
@property (atomic, weak, null_resettable) id<NSStreamDelegate> delegate;

/// Stream current status. Descendants may define custom statuses. Transitions between known statuses are checked for validity
@property (atomic) NSStreamStatus streamStatus;

/// The last stream error encountered. Setting to this property transitions stream to AtError state
@property (atomic, nullable, copy) NSError *streamError;

/// Schedules passed events to be sent to stream's delegate on the next runloop pass
/// @param event Events mask
/// @discussion By default KITBasicInputStream and KITBasicOutputStream check for bytes/space available after every read/write.
///     Use this method to signal delegate about availability at any other circumstances.
- (void)signalStreamEvent:(NSStreamEvent)event;

/// Initializes object
/// @param identity Object used in interface operations like calling delegate callbacks
/// @discussion Pass enclosing stream if KITBasicStream is encapsulated rather than inherited. Otherwise pass nil.
- (instancetype)initWithImposedIdentity:(nullable NSStream<KITBasicStreamPosing> *)identity NS_DESIGNATED_INITIALIZER;

/// The same as initWithImposedIdentity: called with nil
- (instancetype)init;

- (instancetype)initWithData:(NSData *)data NS_UNAVAILABLE;
- (nullable instancetype)initWithURL:(NSURL *)url NS_UNAVAILABLE;

- (void)open NS_REQUIRES_SUPER;
- (void)close NS_REQUIRES_SUPER;

- (BOOL)p_openWithError:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD;
- (BOOL)p_closeWithError:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD;

@end

#pragma mark - KITBasicInputStream

/// Base class simplifying creation of custom input streams. Also see KITBasicStream
/// Descendants must implement the following methods:
///
/// - p_openWithError:
/// - p_closeWithError:
/// - p_hasBytesAvailable
/// - p_getBuffer:length:
/// - p_read:maxLength:error:
@interface KITBasicInputStream: NSInputStream

/// Stream delegate object
/// @discussion By default stream is its own delegate. Setting nil to this property resets it to self
@property (atomic, weak, null_resettable) id<NSStreamDelegate> delegate;

/// Stream current status. Descendants may define custom statuses. Transitions between known statuses are checked for validity
@property (atomic) NSStreamStatus streamStatus;

/// The last stream error encountered. Setting to this property transitions stream to AtError state
@property (atomic, nullable, copy) NSError *streamError;

/// Schedules passed events to be sent to stream's delegate on the next runloop pass
/// @param event Events mask
/// @discussion By default KITBasicInputStream checks for bytes available after every read.
///     Use this method to signal delegate about availability at any other circumstances.
- (void)signalStreamEvent:(NSStreamEvent)event;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initWithData:(NSData *)data NS_UNAVAILABLE;
- (nullable instancetype)initWithURL:(NSURL *)url NS_UNAVAILABLE;

- (void)open NS_REQUIRES_SUPER;
- (void)close NS_REQUIRES_SUPER;
- (BOOL)hasBytesAvailable NS_REQUIRES_SUPER;
- (BOOL)getBuffer:(uint8_t *_Nullable *_Nonnull)buffer length:(NSUInteger *)len NS_REQUIRES_SUPER;
- (NSInteger)read:(uint8_t *)buffer maxLength:(NSUInteger)len NS_REQUIRES_SUPER;

- (BOOL)p_openWithError:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD;
- (BOOL)p_closeWithError:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD;
- (BOOL)p_hasBytesAvailable KIT_ABSTRACT_METHOD;
- (BOOL)p_getBuffer:(uint8_t *_Nullable *_Nonnull)buffer length:(NSUInteger *)len KIT_ABSTRACT_METHOD;
- (NSInteger)p_read:(out uint8_t *)buffer
         maxLength:(NSUInteger)len
             error:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD NS_SWIFT_NOTHROW;

@end

#pragma mark - KITBasicOutputStream

/// Base class simplifying creation of custom output streams. Also see KITBasicStream
/// Descendants must implement the following methods:
///
/// - p_openWithError:
/// - p_closeWithError:
/// - p_hasSpaceAvailable
/// - p_write:maxLength:error:
@interface KITBasicOutputStream: NSOutputStream

/// Stream delegate object
/// @discussion By default stream is its own delegate. Setting nil to this property resets it to self
@property (atomic, weak, null_resettable) id<NSStreamDelegate> delegate;

/// Stream current status. Descendants may define custom statuses. Transitions between known statuses are checked for validity
@property (atomic) NSStreamStatus streamStatus;

/// The last stream error encountered. Setting to this property transitions stream to AtError state
@property (atomic, nullable, copy) NSError *streamError;

/// Schedules passed events to be sent to stream's delegate on the next runloop pass
/// @param event Events mask
/// @discussion By default KITBasicOutputStream checks for space available after every write.
///     Use this method to signal delegate about availability at any other circumstances.
- (void)signalStreamEvent:(NSStreamEvent)event;

- (instancetype)init NS_DESIGNATED_INITIALIZER;
- (instancetype)initToMemory NS_UNAVAILABLE;
- (instancetype)initToBuffer:(uint8_t *)buffer capacity:(NSUInteger)capacity NS_UNAVAILABLE;
- (nullable instancetype)initWithURL:(NSURL *)url append:(BOOL)shouldAppend NS_UNAVAILABLE;

- (void)open NS_REQUIRES_SUPER;
- (void)close NS_REQUIRES_SUPER;
- (BOOL)hasSpaceAvailable NS_REQUIRES_SUPER;
- (NSInteger)write:(const uint8_t *)buffer maxLength:(NSUInteger)len NS_REQUIRES_SUPER;

- (BOOL)p_openWithError:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD;
- (BOOL)p_closeWithError:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD;
- (BOOL)p_hasSpaceAvailable KIT_ABSTRACT_METHOD;
- (NSInteger)p_write:(in const uint8_t *)buffer
          maxLength:(NSUInteger)len
              error:(out NSError *__autoreleasing _Nullable *)error KIT_ABSTRACT_METHOD NS_SWIFT_NOTHROW;

@end

NS_ASSUME_NONNULL_END
