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

#pragma mark - KITHashAlgorithm

typedef NS_ENUM(NSUInteger, KITHashAlgorithm) {
    KITHashAlgorithmMurMur3A    = 8u, // Like the one in https://github.com/aappleby/smhasher

    KITHashAlgorithmAdler32     = 16u, // RFC-1950

    KITHashAlgorithmMD2         = 24u,
    KITHashAlgorithmMD4         = 25u,
    KITHashAlgorithmMD5         = 26u,

    KITHashAlgorithmSHA1        = 32u,

    KITHashAlgorithmSHA224      = 40u,
    KITHashAlgorithmSHA256      = 41u,
    KITHashAlgorithmSHA384      = 42u,
    KITHashAlgorithmSHA512      = 43u,
};

KIT_EXPORT KITHashAlgorithm const KITHashAlgorithmUnknown;
KIT_EXPORT KITHashAlgorithm const KITHashAlgorithmDefault;

typedef NS_OPTIONS(NSUInteger, KITHashAlgorithmTraits) {
    KITHashAlgorithmTraitCryptographic  = 1 << 0,
    KITHashAlgorithmTraitSecure         = 1 << 1,
    KITHashAlgorithmTraitChecksum       = 1 << 2,
    KITHashAlgorithmTraitStable         = 1 << 3,
};

KIT_EXPORT KITHashAlgorithmTraits KITHashAlgorithmTraitsForHashAlgorithm(KITHashAlgorithm);

KIT_EXPORT NSString *KITStringForAlgorithm(KITHashAlgorithm);

#pragma mark - KITHasher

KIT_FINAL_CLASS
@interface KITHasher : NSObject

@property (nonatomic, readonly) KITHashAlgorithm algorithm;

+ (nullable instancetype)hasherWithAlgorithm:(KITHashAlgorithm)algorithm;

- (instancetype)init;
- (nullable instancetype)initWithAlgorithm:(KITHashAlgorithm)algorithm NS_DESIGNATED_INITIALIZER;

- (NSValue *)hashValue;
- (NSData *)hashData;
- (NSString *)hashString;

- (instancetype)combineBytes:(const uint8_t *)buffer length:(size_t)length;
- (instancetype)combineChar:(char)value;
- (instancetype)combineUnsignedChar:(unsigned char)value;
- (instancetype)combineShort:(short)value;
- (instancetype)combineUnsignedShort:(unsigned short)value;
- (instancetype)combineInt:(int)value;
- (instancetype)combineUnsignedInt:(unsigned int)value;
- (instancetype)combineLong:(long)value;
- (instancetype)combineUnsignedLong:(unsigned long)value;
- (instancetype)combineLongLong:(long long)value;
- (instancetype)combineUnsignedLongLong:(unsigned long long)value;
- (instancetype)combineFloat:(float)value;
- (instancetype)combineDouble:(double)value;
- (instancetype)combineBool:(BOOL)value;
- (instancetype)combineInteger:(NSInteger)value;
- (instancetype)combineUnsignedInteger:(NSUInteger)value;

@end

#pragma mark - NSData+KITHasher

@interface NSData(KITHasher)

- (NSValue *)kit_hashValueUsingAlgorithm:(KITHashAlgorithm)algorithm
    NS_SWIFT_NAME(hashValue(algorithm:));
- (NSData *)kit_hashDataUsingAlgorithm:(KITHashAlgorithm)algorithm
    NS_SWIFT_NAME(hashData(algorithm:));
- (NSString *)kit_hashStringUsingAlgorithm:(KITHashAlgorithm)algorithm
    NS_SWIFT_NAME(hashString(algorithm:));

@end

#pragma mark - NSString+KITHasher

@interface NSString(KITHasher)

- (NSValue *)kit_hashValueUsingAlgorithm:(KITHashAlgorithm)algorithm usingEncoding:(NSStringEncoding)encoding
    NS_SWIFT_NAME(hashValue(algorithm:encoding:));
- (NSData *)kit_hashDataUsingAlgorithm:(KITHashAlgorithm)algorithm usingEncoding:(NSStringEncoding)encoding
    NS_SWIFT_NAME(hashData(algorithm:encoding:));
- (NSString *)kit_hashStringUsingAlgorithm:(KITHashAlgorithm)algorithm usingEncoding:(NSStringEncoding)encoding
    NS_SWIFT_NAME(hashString(algorithm:encoding:));

- (NSValue *)kit_hashValueUsingAlgorithm:(KITHashAlgorithm)algorithm
    NS_SWIFT_NAME(hashValue(algorithm:));
- (NSData *)kit_hashDataUsingAlgorithm:(KITHashAlgorithm)algorithm
    NS_SWIFT_NAME(hashData(algorithm:));
- (NSString *)kit_hashStringUsingAlgorithm:(KITHashAlgorithm)algorithm
    NS_SWIFT_NAME(hashString(algorithm:));

@end

#pragma mark - Hash Types

typedef uint32_t KITMurMur3A, KITAdler32;

typedef union KIT_BOXABLE {
    uint8_t bytes[16];
    uint32_t quartiles[4];
    uint64_t halves[2];
} KITMD2, KITMD4, KITMD5;

typedef union KIT_BOXABLE {
    uint8_t bytes[20];
    uint32_t quintiles[5];
} KITSHA1;

typedef union KIT_BOXABLE {
    uint8_t bytes[28];
    uint32_t septiles[7];
} KITSHA224;

typedef union KIT_BOXABLE {
    uint8_t bytes[32];
    uint32_t octiles[8];
    uint64_t quartiles[4];
} KITSHA256;

typedef union KIT_BOXABLE {
    uint8_t bytes[48];
    uint32_t dodeciles[12];
    uint64_t sextiles[6];
} KITSHA384;

typedef union KIT_BOXABLE {
    uint8_t bytes[64];
    uint32_t hexadeciles[16];
    uint64_t octiles[8];
} KITSHA512;

NS_ASSUME_NONNULL_END
