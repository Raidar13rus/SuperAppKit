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

#import <Kulibin/Kulibin.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface KITPromise <ObjectType> (DotSyntax)

/// Map dot syntax.
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^map)(id  _Nullable (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncMap)(dispatch_queue_t _Nonnull, id _Nullable(^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^mapValue)(id _Nullable(^ _Nonnull)(ObjectType _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncMapValue)(dispatch_queue_t _Nonnull, id _Nullable(^ _Nonnull)(ObjectType _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^mapError)(id _Nullable(^ _Nonnull)(NSError * _Nonnull))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncMapError)(dispatch_queue_t _Nonnull, id _Nullable(^ _Nonnull)(NSError * _Nonnull))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

/// Flat map dot syntax.
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^flatMap)(KITPromise *(^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncFlatMap)(dispatch_queue_t _Nonnull, KITPromise *(^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^flatMapValue)(KITPromise * _Nonnull(^ _Nonnull)(ObjectType _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncFlatMapValue)(dispatch_queue_t _Nonnull, KITPromise * _Nonnull(^ _Nonnull)(ObjectType _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^flatMapError)(KITPromise * _Nonnull(^ _Nonnull)(NSError * _Nonnull))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncFlatMapError)(dispatch_queue_t _Nonnull, KITPromise * _Nonnull(^ _Nonnull)(NSError * _Nonnull))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

/// Tap dot syntax.
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^tap)(void (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncTap)(dispatch_queue_t _Nonnull, void (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^tapValue)(void (^ _Nonnull)(ObjectType _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncTapValue)(dispatch_queue_t _Nonnull, void (^ _Nonnull)(ObjectType _Nullable))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^tapError)(void (^ _Nonnull)(NSError * _Nonnull))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");
@property (nonatomic, strong, nonnull, readonly) KITPromise * _Nonnull(^asyncTapError)(dispatch_queue_t _Nonnull, void (^ _Nonnull)(NSError * _Nonnull))
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.");

/// Map dot syntax methods.
- (KITPromise * _Nonnull (^ _Nonnull)(id  _Nullable (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable)))map
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, id  _Nullable (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable)))asyncMap
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

- (KITPromise * _Nonnull (^ _Nonnull)(id  _Nullable (^ _Nonnull)(ObjectType _Nullable)))mapValue NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.")
NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, id  _Nullable (^ _Nonnull)(ObjectType _Nullable)))asyncMapValue
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

- (KITPromise * _Nonnull (^ _Nonnull)(id  _Nullable (^ _Nonnull)(NSError * _Nonnull)))mapError
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, id  _Nullable (^ _Nonnull)(NSError * _Nonnull)))asyncMapError
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

/// Flat map dot syntax methods.
- (KITPromise * _Nonnull (^ _Nonnull)(KITPromise * _Nonnull (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable)))flatMap
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, KITPromise * _Nonnull (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable)))asyncFlatMap
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

- (KITPromise * _Nonnull (^ _Nonnull)(KITPromise * _Nonnull (^ _Nonnull)(ObjectType _Nullable)))flatMapValue
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, KITPromise * _Nonnull (^ _Nonnull)(ObjectType _Nullable)))asyncFlatMapValue
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

- (KITPromise * _Nonnull (^ _Nonnull)(KITPromise * _Nonnull (^ _Nonnull)(NSError * _Nonnull)))flatMapError
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, KITPromise * _Nonnull (^ _Nonnull)(NSError * _Nonnull)))asyncFlatMapError
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

/// Tap dot syntax methods.
- (KITPromise * _Nonnull (^ _Nonnull)(void (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable)))tap
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, void (^ _Nonnull)(ObjectType _Nullable, NSError * _Nullable)))asyncTap
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

- (KITPromise * _Nonnull (^ _Nonnull)(void (^ _Nonnull)(ObjectType _Nullable)))tapValue
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, void (^ _Nonnull)(ObjectType _Nullable)))asyncTapValue
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

- (KITPromise * _Nonnull (^ _Nonnull)(void (^ _Nonnull)(NSError * _Nonnull)))tapError
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;
- (KITPromise * _Nonnull (^ _Nonnull)(dispatch_queue_t _Nonnull, void (^ _Nonnull)(NSError * _Nonnull)))asyncTapError
NS_SWIFT_UNAVAILABLE("Swift uses dot syntax by default.") NS_RETURNS_RETAINED;

@end

NS_ASSUME_NONNULL_END
