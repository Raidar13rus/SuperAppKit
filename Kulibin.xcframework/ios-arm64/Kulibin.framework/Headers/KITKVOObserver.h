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

#ifndef __has_attribute
#define __has_attribute(x) 0  // Compatibility with non-clang compilers
#endif

#if __has_attribute(objc_method_family)
#define BV_OBJC_METHOD_FAMILY_NONE __attribute__((objc_method_family(none)))
#else
#define BV_OBJC_METHOD_FAMILY_NONE
#endif

@interface KITKVOChangeData : NSObject

@property (nonatomic, readonly) NSString *keyPath; //nonnull
@property (nonatomic, readonly) NSKeyValueChange kind; //nonnull
@property (nonatomic, readonly) id newValue;
@property (nonatomic, readonly) id oldValue;
@property (nonatomic, readonly) NSIndexSet *indexes;

+ (instancetype)changeDataWithChangeDictionary:(NSDictionary<NSString *,id> *)change keyPath:(NSString *)keyPath;

- (id)newValue BV_OBJC_METHOD_FAMILY_NONE;

@end



@protocol KITKVOChangeHandler <NSObject>

@required
- (void)handleKVOChange:(KITKVOChangeData *)change;

@end


//make sure to retain KITKVOObserver instance after initialize and set it to nil before observed object dealloc
@interface KITKVOObserver : NSObject

@property (nonatomic, weak) id objectToObserve;
@property (nonatomic) BOOL skipChanges;

- (instancetype)initWithObjectToObserve:(id)objectToObserve;

- (void)observe:(NSString *)keyPath handler:(id<KITKVOChangeHandler>)handler; //will retain handler
- (void)unobserve:(NSString *)keyPath;
- (void)unobserveAll;

@end

@interface KITKVOBlockChangeHandler : NSObject <KITKVOChangeHandler>

+ (instancetype)changeHandlerWithBlock:(void (^)(KITKVOChangeData *change))block;

@end


@interface KITKVOObserver (Convenience)

- (void)observeBoolForKeyPath:(NSString *)keyPath handler:(void(^)(BOOL newValue, BOOL oldValue))handler;
- (void)observeIntegerForKeyPath:(NSString *)keyPath handler:(void(^)(NSInteger newValue, NSInteger oldValue))handler;
- (void)observeDoubleForKeyPath:(NSString *)keyPath handler:(void(^)(double newValue, double oldValue))handler;
- (void)observeFloatForKeyPath:(NSString *)keyPath handler:(void(^)(float newValue, float oldValue))handler;

@end
