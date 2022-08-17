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

#import "KITMacros.h"

#if TARGET_OS_IOS

#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

typedef CGFloat KITScreenSizeCategory NS_TYPED_ENUM NS_SWIFT_NAME(ScreenSizeCategory);

static KITScreenSizeCategory const NS_SWIFT_NAME(inch3_5) KITScreenSizeCategory3_5in = 3.5;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch4) KITScreenSizeCategory4in = 4;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch4_7) KITScreenSizeCategory4_7in = 4.7;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch5_4) KITScreenSizeCategory5_4in = 5.4;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch5_5) KITScreenSizeCategory5_5in = 5.5;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch5_8) KITScreenSizeCategory5_8in = 5.8;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch6_1) KITScreenSizeCategory6_1in = 6.1;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch6_5) KITScreenSizeCategory6_5in = 6.5;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch6_7) KITScreenSizeCategory6_7in = 6.7;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch10_5) KITScreenSizeCategory10_5in = 10.5;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch11) KITScreenSizeCategory11in = 11;
static KITScreenSizeCategory const NS_SWIFT_NAME(inch12_9) KITScreenSizeCategory12_9in = 12.9;

@interface UIScreen (KITDevice)

@property (nonatomic, readonly) CGRect kit_fixedBounds;
@property (nonatomic, readonly) CGFloat kit_individualPixelSize;
@property (nonatomic, readonly) KITScreenSizeCategory kit_sizeCategory;

@end

NS_ASSUME_NONNULL_END

#endif
