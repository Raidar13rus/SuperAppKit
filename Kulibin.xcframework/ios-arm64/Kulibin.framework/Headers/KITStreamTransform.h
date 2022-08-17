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

#pragma mark - <KITStreamTransforming>

typedef NS_ENUM(NSUInteger, KITStreamTransformOperation) {
    KITStreamTransformOperationInitialize,
    KITStreamTransformOperationProcess,
    KITStreamTransformOperationFinalize,
};

/// Protocol defining interface for objects representing abstract data transforms applied through KITTransformingStream
@protocol KITStreamTransforming <NSObject, NSCopying>

/// Asks transform to process single batch of data
/// @param operation Current stage in the whole operation cycle
/// @param srcBuf Buffer containing bytes to process
/// @param srcLen On enter contains number of bytes available in srcBuf. On exit contains number of bytes left in srcBuf
/// @param dstBuf Buffer to output data in
/// @param dstLen On enter contains space in bytes available in srcBuf. On exit contains number of space left in srcBuf
/// @param error If NO is returned, an NSError object describing the error
/// @discussion At first this method is called repeatedly with operation set to KITStreamTransformOperationInitialize
///     and *srcLen == 0 until it stops prodicing data.
///     This allows transform to write prologue if necessary before any actual data is processed.
///     After that at each step this method is called with operation set to KITStreamTransformOperationProcess.
///     This is the only step where transform is allowed to neither produce or consume any data, though
///     doing so may lead to congestion.
///     After all data is processed, this method is called with operation set to KITStreamTransformOperationFinalze and
///     *srcLen == 0 until it again stops producing data. This allows transform to write epilogue if necessary.
- (BOOL)performOperation:(KITStreamTransformOperation)operation
                onBuffer:(in const uint8_t *KIT_NONOVERLAPPING)srcBuf
                  ofSize:(inout size_t *KIT_NONOVERLAPPING)srcLen
      outputtingToBuffer:(out uint8_t *KIT_NONOVERLAPPING)dstBuf
                  ofSize:(inout size_t *KIT_NONOVERLAPPING)dstLen
               withError:(out NSError *__autoreleasing _Nullable *_Nullable)error NS_SWIFT_NAME(perfrom(_:from:size:to:size:));

@optional

/// Ratio between data before and after conversion.
/// Enclosing stream will try to match buffer sizes according to this value.
@property (nonatomic, readonly) double approximateTransformDataSizeRatio;

@end

#pragma mark - NSData+KITStreamTransforming

@interface NSData(KITStreamTransforming)

/// Applies transform to self
/// @param transform transform to be appled
/// @param error Output error object
- (NSData *_Nullable)dataByApplyingTransform:(id<KITStreamTransforming>)transform error:(NSError **)error;

@end

#pragma mark - KITBlockStreamTransform

typedef BOOL (^KITStreamTransformingBlock)(
    KITStreamTransformOperation,
    const uint8_t *,
    size_t *,
    uint8_t *,
    size_t *,
    NSError *__autoreleasing _Nullable *_Nullable
);

/// Transform that uses block at each call to performOperation:onBuffer:ofSize:outputtingToBuffer:ofSize:withError:
KIT_FINAL_CLASS
@interface KITBlockStreamTransform : NSObject<KITStreamTransforming>

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/// Initializes object with block
/// @param block block object with signature matching to the one of
/// performOperation:onBuffer:ofSize:outputtingToBuffer:ofSize:withError:
- (instancetype)initWithBlock:(KITStreamTransformingBlock)block;

@end

#pragma mark - KITIdentityStreamTransform

/// Transform that leaves data unchanged
KIT_FINAL_CLASS
@interface KITIdentityStreamTransform : NSObject<KITStreamTransforming>
@end

NS_ASSUME_NONNULL_END
