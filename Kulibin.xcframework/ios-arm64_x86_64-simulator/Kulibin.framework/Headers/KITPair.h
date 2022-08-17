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

KIT_FINAL_CLASS
@interface KITPair<L, R> : NSObject

@property (nonatomic, strong, nullable) L first;
@property (nonatomic, strong, nullable) R second;

@property (nonatomic, strong, nullable) L key;
@property (nonatomic, strong, nullable) R value;

@property (nonatomic, strong, nullable) L left;
@property (nonatomic, strong, nullable) R right;

@property (nonatomic, readonly, nullable) KITPair<L, R> *nonEmptyOrNil;
@property (nonatomic, readonly) KITPair<R, L> *flip;

+ (instancetype)pair:(_Nullable L)first with:(_Nullable R)second;

+ (instancetype)pairWithFirst:(_Nullable L)first second:(_Nullable R)second;
+ (instancetype)pairWithKey:(_Nullable L)key value:(_Nullable R)value;
+ (instancetype)pairWithLeft:(_Nullable L)left right:(_Nullable R)right;

- (instancetype)initWithFirst:(_Nullable L)first second:(_Nullable R)second;
- (instancetype)initWithKey:(_Nullable L)key value:(_Nullable R)value;
- (instancetype)initWithLeft:(_Nullable L)key right:(_Nullable R)value;

@end

static inline KITPair *KITMakePair(_Nullable id l, _Nullable id r) {
    return [KITPair pair:l with:r];
}

NS_ASSUME_NONNULL_END
