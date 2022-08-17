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
#import "KITCommon.h"

NS_ASSUME_NONNULL_BEGIN

typedef NS_ENUM(NSInteger, KITCompressionOperation) {
    KITCompressionOperationCompress = 0,
    KITCompressionOperationDecompress = 1,
};

typedef NS_ENUM(NSInteger, KITCompressionAlgorithm) {
    KITCompressionAlgorithmLZ4      = 0x100,
    KITCompressionAlgorithmZLIB     = 0x205,
    KITCompressionAlgorithmLZMA     = 0x306,
    KITCompressionAlgorithmLZ4_RAW  = 0x101,
    KITCompressionAlgorithmLZFSE    = 0x801,
};

FOUNDATION_EXPORT BOOL KITCompress(
    KITCompressionOperation operation,
    KITCompressionAlgorithm algorithm,
    NSInputStream *input,
    NSOutputStream *output,
    BOOL (NS_NOESCAPE ^_Nullable interrupt)(uint8_t *src, size_t srcLen, uint8_t *dst, size_t dstLen),
    NSError *_Nullable __autoreleasing *_Nullable error
) NS_REFINED_FOR_SWIFT;

FOUNDATION_EXPORT BOOL KITZIP(
    NSInputStream *input,
    NSOutputStream *output,
    NSError *_Nullable __autoreleasing *_Nullable error
) NS_REFINED_FOR_SWIFT; // ZLIB RFC-1950

#pragma mark NSData+KITCompress

@interface NSData (KITCompress)

- (NSData *_Nullable)kit_dataByPerformingCompressionOperation:(KITCompressionOperation)operation
                                               usingAlgorithm:(KITCompressionAlgorithm)algorithm
                                                        error:(out NSError *__autoreleasing _Nullable *_Nullable)error KIT_NODISCARD;

@end

NS_ASSUME_NONNULL_END
