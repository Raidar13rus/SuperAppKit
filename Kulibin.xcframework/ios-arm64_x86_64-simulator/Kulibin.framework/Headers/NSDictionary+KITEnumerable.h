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
#import "KITCollection.h"
#import "KITPair.h"

NS_ASSUME_NONNULL_BEGIN

#pragma mark - <KITEnumerable>

@interface NSDictionary<K, V>(KITEnumerable)<KITEnumerable>

- (NSEnumerator<KITPair<K, V> *> *)kit_enumerator;
- (NSArray<KITPair<K, V> *> *)kit_array;
- (NSSet<KITPair<K, V> *> *)kit_set;
- (NSSet<KITPair<K, V> *> *)kit_setResolvingConflictsBy:(KITPair<K, V> *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair<K, V> *existing, KITPair<K, V> *replacing))block;
- (NSOrderedSet<KITPair<K, V> *> *)kit_orderedSet;
- (NSOrderedSet<KITPair<K, V> *> *)kit_orderedSetResolvingConflictsBy:(KITPair<K, V> *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair<K, V> *existing, KITPair<K, V> *replacing))block;
- (NSDictionary<K, V> *)kit_dictionary;
- (NSDictionary<K, V> *)kit_dictionaryResolvingConflictsBy:(KITPair<K, V> *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair<K, V> *existing, KITPair<K, V> *replacing))block;
- (NSDictionary *)kit_dictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(KITPair<K, V> *obj))mapper;
- (NSDictionary *)kit_dictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(KITPair<K, V> *obj))mapper
            resolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *existing, KITPair *replacing))block;

- (void)kit_forEach:(void (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;
- (void)kit_forEachExt:(void (NS_NOESCAPE ^)(KITPair<K, V> *obj, NSUInteger i, BOOL *stop))block;

- (NSArray *)kit_map:(id (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;
- (NSArray *)kit_mapExt:(id (NS_NOESCAPE ^)(KITPair<K, V> *obj, NSUInteger i, BOOL *stop))block;
- (NSArray *)kit_compactMap:(_Nullable id (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;
- (NSArray *)kit_compactMapExt:(_Nullable id (NS_NOESCAPE ^)(KITPair<K, V> *obj, NSUInteger i, BOOL *stop))block;
- (NSArray *)kit_flatMap:(_Nullable id (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;
- (NSArray *)kit_flatMapExt:(_Nullable id (NS_NOESCAPE ^)(KITPair<K, V> *obj, NSUInteger i, BOOL *stop))block;

- (NSArray<KITPair<K, V> *> *)kit_prefix:(NSUInteger)numberOfElements;
- (NSArray<KITPair<K, V> *> *)kit_prefixWhile:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;
- (NSArray<KITPair<K, V> *> *)kit_suffix:(NSUInteger)numberOfElements;
- (NSArray<KITPair<K, V> *> *)kit_suffixWhile:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;

- (NSArray<KITPair<K, V> *> *)kit_dropFirst:(NSUInteger)numberOfElements;
- (NSArray<KITPair<K, V> *> *)kit_dropFirstWhile:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;
- (NSArray<KITPair<K, V> *> *)kit_dropLast:(NSUInteger)numberOfElements;
- (NSArray<KITPair<K, V> *> *)kit_dropLastWhile:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;

- (NSArray<KITPair<K, V> *> *)kit_subrange:(NSRange)range;

- (NSArray<KITPair<K, V> *> *)kit_filter:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;

- (NSArray *)kit_flatten;
- (NSArray *)kit_flattenToLevel:(NSUInteger)level;

- (NSArray<KITPair<KITPair<K, V> *, id> *> *)kit_zipIntoPairs:(id<KITEnumerable>)other;
- (NSArray<NSArray<KITPair<K, V> *> *> *)kit_split:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;
- (NSArray<NSArray<KITPair<K, V> *> *> *)kit_group:(_Nullable id (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;
- (NSDictionary<id, NSArray<KITPair<K, V> *> *> *)kit_groupByKey:(_Nullable id (NS_NOESCAPE ^)(KITPair<K, V> *obj))block;

- (_Nullable id)kit_reduceFrom:(_Nullable id)acc usingBlock:(_Nullable id (NS_NOESCAPE ^)(_Nullable id acc, KITPair<K, V> *obj))block;
- (_Nullable id)kit_reduceInto:(_Nullable id)acc usingBlock:(void (NS_NOESCAPE ^)(__strong _Nullable id *_Nonnull acc, KITPair<K, V> *obj))block;

- (_Nullable id)kit_foldLeft:(_Nullable id (NS_NOESCAPE ^)(_Nullable id l, KITPair<K, V> *r))block;
- (_Nullable id)kit_foldRight:(_Nullable id (NS_NOESCAPE ^)(_Nullable id l, KITPair<K, V> *r))block;

- (KITPair<K, V> *_Nullable)kit_firstWhere:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;
- (KITPair<K, V> *_Nullable)kit_lastWhere:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;
- (NSUInteger)kit_countWhere:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))filter;

- (BOOL)kit_allSatisfy:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;
- (BOOL)kit_containsWhere:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *obj))predicate;
- (BOOL)kit_equalsToSequence:(_Nullable id<KITEnumerable>)seq;

@end

#pragma mark - KITAdditions

@interface NSDictionary<K, V>(KITCollectionAdditions)

- (NSDictionary<V, K> *)kit_inverseDictionary;
- (NSDictionary<V, K> *)kit_inverseDictionaryResolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *exising, KITPair *replacing))block;

- (NSDictionary<K, V> *)kit_filterDictionary:(BOOL (NS_NOESCAPE ^)(KITPair<K, V> *))predicate;

- (NSDictionary *)kit_mapDictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(KITPair<K, V> *))block
               resolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *existing, KITPair *replacing))resolver;

- (NSDictionary<__kindof K, __kindof V> *)kit_mergeWithDictionary:(NSDictionary *)dictionary;
- (NSDictionary<__kindof K, __kindof V> *)kit_mergeWithDictionary:(NSDictionary *)dictionary
                                             resolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *exising, KITPair *replacing))block;

@end

NS_ASSUME_NONNULL_END
