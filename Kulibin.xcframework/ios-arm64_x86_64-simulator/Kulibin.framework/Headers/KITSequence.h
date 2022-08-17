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

@protocol KITCollection;
@class KITPair;

typedef NS_OPTIONS(NSUInteger, KITEnumerationOptions) {
    KITEnumerationOptionsReverse
};

typedef NS_OPTIONS(NSUInteger, KITMappingOptions) {
    KITMappingOptionsCompact = (1 << 1),
    KITMappingOptionsFlatten = (1 << 2),
};

typedef NS_OPTIONS(NSUInteger, KITZippingOptions) {
    KITZippingOptionPadShorterWithNil = 1 << 1,
    KITZippingOptionCompact = 2 << 1,
};

typedef NS_OPTIONS(NSUInteger, KITSplittingOptions) {
    KITSplittingOptionOmitEmptySubsequences = 1 << 1,
};

static inline BOOL (^KITAlwaysYesPredicate(void))(id<NSObject>) {
    return ^BOOL (__unused id<NSObject> obj) { return YES; };
}

static inline BOOL (^KITObjectIsKindOfClassPredicate(__unsafe_unretained Class cls))(id<NSObject>) {
    return [^BOOL (id<NSObject> obj) { return [obj isKindOfClass:cls]; } copy];
}

static inline BOOL (^KITObjectConformsToProtocol(__unsafe_unretained Protocol *proto))(id<NSObject>) {
    return [^BOOL (id<NSObject> obj) { return [obj conformsToProtocol:proto]; } copy];
}

static inline BOOL (^KITObjectEqualsToObject(id<NSObject> ex))(id<NSObject> obj) {
    return [^BOOL (id<NSObject> obj) { return KITAreObjectsEqual(obj, ex); } copy];
}

@protocol KITEnumerable <NSObject, NSFastEnumeration>

- (NSEnumerator *)kit_enumerator;
- (NSArray *)kit_array;
- (NSSet *)kit_set;
- (NSSet *)kit_setResolvingConflictsBy:(id _Nullable (NS_NOESCAPE ^_Nullable)(id existing, id replacing))block;
- (NSOrderedSet *)kit_orderedSet;
- (NSOrderedSet *)kit_orderedSetResolvingConflictsBy:(id _Nullable (NS_NOESCAPE ^_Nullable)(id existing, id replacing))block;
- (NSDictionary *)kit_dictionary;
- (NSDictionary *)kit_dictionaryResolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *existing, KITPair *replacing))block;
- (NSDictionary *)kit_dictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(id obj))mapper;
- (NSDictionary *)kit_dictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(id obj))mapper
            resolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *existing, KITPair *replacing))block;

- (void)kit_forEach:(void (NS_NOESCAPE ^)(id obj))block;
- (void)kit_forEachExt:(void (NS_NOESCAPE ^)(id obj, NSUInteger i, BOOL *stop))block;

- (id<KITEnumerable>)kit_map:(id (NS_NOESCAPE ^)(id obj))block;
- (id<KITEnumerable>)kit_mapExt:(id (NS_NOESCAPE ^)(id obj, NSUInteger i, BOOL *stop))block;
- (id<KITEnumerable>)kit_compactMap:(_Nullable id (NS_NOESCAPE ^)(id obj))block;
- (id<KITEnumerable>)kit_compactMapExt:(_Nullable id (NS_NOESCAPE ^)(id obj, NSUInteger i, BOOL *stop))block;
- (id<KITEnumerable>)kit_flatMap:(_Nullable id (NS_NOESCAPE ^)(id obj))block;
- (id<KITEnumerable>)kit_flatMapExt:(_Nullable id (NS_NOESCAPE ^)(id obj, NSUInteger i, BOOL *stop))block;

- (id<KITEnumerable>)kit_prefix:(NSUInteger)numberOfElements;
- (id<KITEnumerable>)kit_prefixWhile:(BOOL (NS_NOESCAPE ^)(id obj))predicate;
- (id<KITEnumerable>)kit_suffix:(NSUInteger)numberOfElements;
- (id<KITEnumerable>)kit_suffixWhile:(BOOL (NS_NOESCAPE ^)(id obj))predicate;

- (id<KITEnumerable>)kit_dropFirst:(NSUInteger)numberOfElements;
- (id<KITEnumerable>)kit_dropFirstWhile:(BOOL (NS_NOESCAPE ^)(id obj))predicate;
- (id<KITEnumerable>)kit_dropLast:(NSUInteger)numberOfElements;
- (id<KITEnumerable>)kit_dropLastWhile:(BOOL (NS_NOESCAPE ^)(id obj))predicate;

- (id<KITEnumerable>)kit_subrange:(NSRange)range;

- (id<KITEnumerable>)kit_filter:(BOOL (NS_NOESCAPE ^)(id obj))predicate;

- (id<KITEnumerable>)kit_flatten;
- (id<KITEnumerable>)kit_flattenToLevel:(NSUInteger)level;

- (id<KITEnumerable>)kit_zipIntoPairs:(id<KITEnumerable>)other;
- (id<KITEnumerable>)kit_split:(BOOL (NS_NOESCAPE ^)(id obj))isSeparator;
- (id<KITEnumerable>)kit_group:(_Nullable id (NS_NOESCAPE ^)(id obj))block;
- (NSDictionary *)kit_groupByKey:(_Nullable id (NS_NOESCAPE ^)(id obj))block;

- (nullable id)kit_reduceFrom:(nullable id)acc usingBlock:(nullable id (NS_NOESCAPE ^)(id acc, id obj))block;
- (nullable id)kit_reduceInto:(nullable id)acc usingBlock:(void (NS_NOESCAPE ^)(__strong _Nullable id *_Nonnull acc, id obj))block;

- (nullable id)kit_foldLeft:(_Nullable id (NS_NOESCAPE ^)(id _Nullable l, id r))block;
- (nullable id)kit_foldRight:(_Nullable id (NS_NOESCAPE ^)(id _Nullable l, id r))block;

- (nullable id)kit_firstWhere:(BOOL (NS_NOESCAPE ^)(id obj))predicate;
- (nullable id)kit_lastWhere:(BOOL (NS_NOESCAPE ^)(id obj))predicate;
- (NSUInteger)kit_countWhere:(BOOL (NS_NOESCAPE ^)(id obj))filter;

- (BOOL)kit_allSatisfy:(BOOL (NS_NOESCAPE ^)(id obj))predicate;
- (BOOL)kit_containsWhere:(BOOL (NS_NOESCAPE ^)(id obj))predicate;
- (BOOL)kit_equalsToSequence:(_Nullable id<KITEnumerable>)seq;

@end

static inline NSArray *KITConcatEnumerables(id<NSFastEnumeration> l, id<NSFastEnumeration> r) {
    NSMutableArray *result = NSMutableArray.array;
    for (id obj in l) {
        [result addObject:obj];
    }
    for (id obj in r) {
        [result addObject:obj];
    }
    return result;
}

NS_ASSUME_NONNULL_END
