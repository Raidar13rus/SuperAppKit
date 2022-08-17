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

@interface NSEnumerator<T>(KITEnumerable)<KITEnumerable>

- (NSEnumerator<T> *)kit_enumerator;
- (NSArray<T> *)kit_array;
- (NSSet<T> *)kit_set;
- (NSSet<T> *)kit_setResolvingConflictsBy:(T _Nullable (NS_NOESCAPE ^_Nullable)(T existing, T replacing))block;
- (NSOrderedSet<T> *)kit_orderedSet;
- (NSOrderedSet<T> *)kit_orderedSetResolvingConflictsBy:(T _Nullable (NS_NOESCAPE ^_Nullable)(T existing, T replacing))block;
- (NSDictionary *)kit_dictionary;
- (NSDictionary *)kit_dictionaryResolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *existing, KITPair *replacing))block;
- (NSDictionary *)kit_dictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(T obj))mapper;
- (NSDictionary *)kit_dictionary:(KITPair *_Nullable (NS_NOESCAPE ^)(T obj))mapper
            resolvingConflictsBy:(KITPair *_Nullable (NS_NOESCAPE ^_Nullable)(KITPair *existing, KITPair *replacing))block;

- (void)kit_forEach:(void (NS_NOESCAPE ^)(T obj))block;
- (void)kit_forEachExt:(void (NS_NOESCAPE ^)(T obj, NSUInteger i, BOOL *stop))block;

- (NSEnumerator *)kit_map:(id (NS_NOESCAPE ^)(T obj))block;
- (NSEnumerator *)kit_mapExt:(id (NS_NOESCAPE ^)(T obj, NSUInteger i, BOOL *stop))block;
- (NSEnumerator *)kit_compactMap:(nullable id (NS_NOESCAPE ^)(T obj))block;
- (NSEnumerator *)kit_compactMapExt:(nullable id (NS_NOESCAPE ^)(T obj, NSUInteger i, BOOL *stop))block;
- (NSEnumerator *)kit_flatMap:(_Nullable id (NS_NOESCAPE ^)(T obj))block;
- (NSEnumerator *)kit_flatMapExt:(_Nullable id (NS_NOESCAPE ^)(T obj, NSUInteger i, BOOL *stop))block;

- (NSEnumerator<T> *)kit_prefix:(NSUInteger)numberOfElements;
- (NSEnumerator<T> *)kit_prefixWhile:(BOOL (NS_NOESCAPE ^)(T obj))predicate;
- (NSEnumerator<T> *)kit_suffix:(NSUInteger)numberOfElements;
- (NSEnumerator<T> *)kit_suffixWhile:(BOOL (NS_NOESCAPE ^)(T obj))predicate;

- (NSEnumerator<T> *)kit_dropFirst:(NSUInteger)numberOfElements;
- (NSEnumerator<T> *)kit_dropFirstWhile:(BOOL (NS_NOESCAPE ^)(T obj))predicate;
- (NSEnumerator<T> *)kit_dropLast:(NSUInteger)numberOfElements;
- (NSEnumerator<T> *)kit_dropLastWhile:(BOOL (NS_NOESCAPE ^)(T obj))predicate;

- (NSEnumerator<T> *)kit_subrange:(NSRange)range;

- (NSEnumerator<T> *)kit_filter:(BOOL (NS_NOESCAPE ^)(T obj))predicate;

- (NSEnumerator *)kit_flatten;
- (NSEnumerator *)kit_flattenToLevel:(NSUInteger)level;

- (NSEnumerator<KITPair<T, id> *> *)kit_zipIntoPairs:(id<KITEnumerable>)other;
- (NSEnumerator<NSArray<T> *> *)kit_split:(BOOL (NS_NOESCAPE ^)(T obj))block;
- (NSDictionary<id, NSArray<T> *> *)kit_groupByKey:(_Nullable id (NS_NOESCAPE ^)(T obj))block;
- (NSEnumerator *)kit_group:(_Nullable id (NS_NOESCAPE ^)(id obj))block;

- (nullable id)kit_reduceFrom:(nullable id)acc usingBlock:(nullable id (NS_NOESCAPE ^)(id acc, T obj))block;
- (nullable id)kit_reduceInto:(nullable id)acc usingBlock:(void (NS_NOESCAPE ^)(__strong _Nullable id *_Nonnull acc, id obj))block;

- (nullable id)kit_foldLeft:(nullable id (NS_NOESCAPE ^)(id _Nullable l, T r))block;
- (nullable id)kit_foldRight:(nullable id (NS_NOESCAPE ^)(id _Nullable l, T r))block;

- (nullable T)kit_firstWhere:(BOOL (NS_NOESCAPE ^)(T obj))predicate;
- (nullable T)kit_lastWhere:(BOOL (NS_NOESCAPE ^)(T obj))predicate;
- (NSUInteger)kit_countWhere:(BOOL (NS_NOESCAPE ^)(T obj))filter;

- (BOOL)kit_allSatisfy:(BOOL (NS_NOESCAPE ^)(T obj))predicate;
- (BOOL)kit_containsWhere:(BOOL (NS_NOESCAPE ^)(T obj))predicate;
- (BOOL)kit_equalsToSequence:(id<KITEnumerable>)seq;

@end

NS_ASSUME_NONNULL_END
