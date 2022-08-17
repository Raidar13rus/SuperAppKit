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
#import <Kulibin/KITMacros.h>

NS_ASSUME_NONNULL_BEGIN

#pragma mark - KITOnce

NS_REFINED_FOR_SWIFT
KIT_FINAL_CLASS
/// Thread safe affine-type-like value
/// Provides access to stored value only once. Sequential access produces nil.
@interface KITOnce<__covariant ObjectType> : NSObject<NSCopying>

@property (nonatomic, readonly, nullable) ObjectType value;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithValue:(ObjectType)value NS_DESIGNATED_INITIALIZER;

@end

#pragma mark - KITLazy

KIT_FINAL_CLASS
/// Thread safe lazy value
/// Only initializes value on the first access. Sequential access produces stored value.
@interface KITLazy<__covariant ObjectType> : NSObject

@property (nonatomic, readonly) ObjectType value;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithBlock:(ObjectType (^)(void))block NS_DESIGNATED_INITIALIZER;

@end

KIT_FINAL_CLASS
/// Shared value
/// Provides means for both mutating and non-mutating access in synchronized fashion
@interface KITShared<ObjectType> : NSObject

@property (nonatomic, readonly, nullable) ObjectType value;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithValue:(nullable ObjectType)value;

- (id _Nullable)withExclusiveAccess:(BOOL)isExclusive
                            perform:(id _Nullable (^NS_NOESCAPE)(__strong ObjectType _Nullable *_Nonnull))block;

@end

#pragma mark - KITCache

KIT_FINAL_CLASS
/// Memoized key-value-like storage
@interface KITMemoized<__contravariant KeyType, __covariant ValueType> : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithProducerBlock:(ValueType (^)(KeyType))make NS_DESIGNATED_INITIALIZER;

- (ValueType)objectForKeyedSubscript:(KeyType)key;

@end

NS_ASSUME_NONNULL_END

