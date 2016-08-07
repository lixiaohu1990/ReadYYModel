//
//  YYClassInfo.h
//  YYModel <https://github.com/ibireme/YYModel>
//
//  Created by ibireme on 15/5/9.
//  Copyright (c) 2015 ibireme.
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <Foundation/Foundation.h>
#import <objc/runtime.h>

NS_ASSUME_NONNULL_BEGIN

/**
 Type encoding's type.
 */
typedef NS_OPTIONS(NSUInteger, YYEncodingType) {
    
//    #1 变量的数据类型
    // 低八位的值： 变量的数据类型
    YYEncodingTypeMask       = 0xFF, ///< mask of type value 1111 1111
    YYEncodingTypeUnknown    = 0, ///< unknown
    YYEncodingTypeVoid       = 1, ///< void
    YYEncodingTypeBool       = 2, ///< bool
    YYEncodingTypeInt8       = 3, ///< char / BOOL
    YYEncodingTypeUInt8      = 4, ///< unsigned char
    YYEncodingTypeInt16      = 5, ///< short
    YYEncodingTypeUInt16     = 6, ///< unsigned short
    YYEncodingTypeInt32      = 7, ///< int
    YYEncodingTypeUInt32     = 8, ///< unsigned int
    YYEncodingTypeInt64      = 9, ///< long long
    YYEncodingTypeUInt64     = 10, ///< unsigned long long
    YYEncodingTypeFloat      = 11, ///< float
    YYEncodingTypeDouble     = 12, ///< double
    YYEncodingTypeLongDouble = 13, ///< long double
    
    // 1. 自定义类型 2.NSObject
    YYEncodingTypeObject     = 14, ///< id
    // Class 类型
    YYEncodingTypeClass      = 15, ///< Class
    // SEL字符串
    YYEncodingTypeSEL        = 16, ///< SEL
    YYEncodingTypeBlock      = 17, ///< block
    YYEncodingTypePointer    = 18, ///< void*
    YYEncodingTypeStruct     = 19, ///< struct
    YYEncodingTypeUnion      = 20, ///< union
    // 字符串
    YYEncodingTypeCString    = 21, ///< char*
    //数组
    YYEncodingTypeCArray     = 22, ///< char[10] (for example)
    
    
//    ＃2 method的attributes
    // 取得8~16位的值类型 ： 方法类型
    YYEncodingTypeQualifierMask   = 0xFF00,   ///< mask of qualifier 1111 1111 0000 0000
    YYEncodingTypeQualifierConst  = 1 << 8,  ///< const 1 0000 0000
    YYEncodingTypeQualifierIn     = 1 << 9,  ///< in
    YYEncodingTypeQualifierInout  = 1 << 10, ///< inout
    YYEncodingTypeQualifierOut    = 1 << 11, ///< out
    YYEncodingTypeQualifierBycopy = 1 << 12, ///< bycopy
    YYEncodingTypeQualifierByref  = 1 << 13, ///< byref
    YYEncodingTypeQualifierOneway = 1 << 14, ///< oneway
    
    
//    ＃3 变量的attributes
    // 取得16～24位的值类型 ： 属性的附加修饰类型
    YYEncodingTypePropertyMask         = 0xFF0000, ///< mask of property
    YYEncodingTypePropertyReadonly     = 1 << 16, ///< readonly
    YYEncodingTypePropertyCopy         = 1 << 17, ///< copy
    YYEncodingTypePropertyRetain       = 1 << 18, ///< retain
    YYEncodingTypePropertyNonatomic    = 1 << 19, ///< nonatomic
    YYEncodingTypePropertyWeak         = 1 << 20, ///< weak
    YYEncodingTypePropertyCustomGetter = 1 << 21, ///< getter=
    YYEncodingTypePropertyCustomSetter = 1 << 22, ///< setter=
    YYEncodingTypePropertyDynamic      = 1 << 23, ///< @dynamic
};

/**
 Get the type from a Type-Encoding string.
 
 @discussion See also:
 https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtTypeEncodings.html
 https://developer.apple.com/library/mac/documentation/Cocoa/Conceptual/ObjCRuntimeGuide/Articles/ocrtPropertyIntrospection.html
 
 @param typeEncoding  A Type-Encoding string.
 @return The encoding type.
 */
YYEncodingType YYEncodingGetType(const char *typeEncoding);


/**
 Instance variable information.
 */

//YYClassIvarInfo 对 Class的Ivar进行了进行封装增加描述

@interface YYClassIvarInfo : NSObject

//这里为什么要对这个ivar的内存偏移地址和类型等这些，这里这样做是为了后面处理起来的时候，可以直接在外面暴露的地方获取到这些属性，而不需要再用runtime获取对应的内容，也可以增加内存的命中率。

@property (nonatomic, assign, readonly) Ivar ivar;              ///< ivar opaque struct
//变量名字
@property (nonatomic, strong, readonly) NSString *name;         ///< Ivar's name
//变量便宜地址
@property (nonatomic, assign, readonly) ptrdiff_t offset;       ///< Ivar's offset
//变量的编码类型
@property (nonatomic, strong, readonly) NSString *typeEncoding; ///< Ivar's type encoding
//转化成YYType类型
@property (nonatomic, assign, readonly) YYEncodingType type;    ///< Ivar's type

/**
 Creates and returns an ivar info object.
 
 @param ivar ivar opaque struct
 @return A new object, or nil if an error occurs.
 */

/**
 通过一个ivar 将YYClassIvarInfo属性描述填充
 */
- (instancetype)initWithIvar:(Ivar)ivar;
@end


/**
 Method information.
 */

//YYClassMethodInfo 对 Class 的 Method进行封装增加描述

@interface YYClassMethodInfo : NSObject
@property (nonatomic, assign, readonly) Method method;                  ///< method opaque struct
//方法名
@property (nonatomic, strong, readonly) NSString *name;                 ///< method name
//sel:即C字符串
@property (nonatomic, assign, readonly) SEL sel;                        ///< method's selector
//SEL对应的IMP
@property (nonatomic, assign, readonly) IMP imp;                        ///< method's implementation
//方法的编码
@property (nonatomic, strong, readonly) NSString *typeEncoding;         ///< method's parameter and return types
//返回值类型
@property (nonatomic, strong, readonly) NSString *returnTypeEncoding;   ///< return value's type
//方法参数的类型，用数组来装
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *argumentTypeEncodings; ///< array of arguments' type

/**
 Creates and returns a method info object.
 
 @param method method opaque struct
 @return A new object, or nil if an error occurs.
 */

/**
 通过传入一个Method对Method进行填充描述信息
 */
- (instancetype)initWithMethod:(Method)method;
@end


/**
 Property information.
 */

//YYClassPropertyInfo 对 Class 的 Property进行了封装描述

@interface YYClassPropertyInfo : NSObject
@property (nonatomic, assign, readonly) objc_property_t property; ///< property's opaque struct
//属性名
@property (nonatomic, strong, readonly) NSString *name;           ///< property's name
//属性类型
@property (nonatomic, assign, readonly) YYEncodingType type;      ///< property's type
//属性编码
@property (nonatomic, strong, readonly) NSString *typeEncoding;   ///< property's encoding value
//属性对应的ivar名字
@property (nonatomic, strong, readonly) NSString *ivarName;       ///< property's ivar name
//属性的class
@property (nullable, nonatomic, assign, readonly) Class cls;      ///< may be nil
@property (nullable, nonatomic, strong, readonly) NSArray<NSString *> *protocols; ///< may nil
@property (nonatomic, assign, readonly) SEL getter;               ///< getter (nonnull)
@property (nonatomic, assign, readonly) SEL setter;               ///< setter (nonnull)

/**
 Creates and returns a property info object.
 
 @param property property opaque struct
 @return A new object, or nil if an error occurs.
 */
/**
 根据property取得填充对应的描述
 */
- (instancetype)initWithProperty:(objc_property_t)property;
@end


/**
 Class information for a class.
 */
@interface YYClassInfo : NSObject
//类
@property (nonatomic, assign, readonly) Class cls; ///< class object
//父类
@property (nullable, nonatomic, assign, readonly) Class superCls; ///< super class object
//元类
@property (nullable, nonatomic, assign, readonly) Class metaCls;  ///< class's meta class object
//是否为元类
@property (nonatomic, readonly) BOOL isMeta; ///< whether this class is meta class
//类名
@property (nonatomic, strong, readonly) NSString *name; ///< class name
//父类的信息
@property (nullable, nonatomic, strong, readonly) YYClassInfo *superClassInfo; ///< super class's class info
///< ivars 用字典来装，与YYClassIvarInfo一一对应
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, YYClassIvarInfo *> *ivarInfos; ///< ivars
///< methods用字典来装，与YYClassMethodInfo一一对应
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, YYClassMethodInfo *> *methodInfos; ///< methods
///< properties用字典来装，与YYClassPropertyInfo一一对应
@property (nullable, nonatomic, strong, readonly) NSDictionary<NSString *, YYClassPropertyInfo *> *propertyInfos; ///< properties

/**
 If the class is changed (for example: you add a method to this class with
 'class_addMethod()'), you should call this method to refresh the class info cache.
 
 After called this method, `needUpdate` will returns `YES`, and you should call 
 'classInfoWithClass' or 'classInfoWithClassName' to get the updated class info.
 */

/**
 当class中有内容被修改了，如增加了一个新的方法，需要调用这个方法进行刷新class的信息，这个方法调用后会将needUpdate方法中的返回值设置为YES，从而需要调用classInfoWithClass或者classInfoWithClassName来获取刷新class的信息
 */

- (void)setNeedUpdate;

/**
 If this method returns `YES`, you should stop using this instance and call
 `classInfoWithClass` or `classInfoWithClassName` to get the updated class info.
 
 @return Whether this class info need update.
 */


/**
 classInfo是否需要刷新，当返回值为YES的时候，需要停止使用改Instance
 */
- (BOOL)needUpdate;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param cls A class.
 @return A class info, or nil if an error occurs.
 */

/**
 获得cls的详细信息，并刷新
 */
+ (nullable instancetype)classInfoWithClass:(Class)cls;

/**
 Get the class info of a specified Class.
 
 @discussion This method will cache the class info and super-class info
 at the first access to the Class. This method is thread-safe.
 
 @param className A class name.
 @return A class info, or nil if an error occurs.
 */

/**
 获得cls的详细信息，并刷新
 */
+ (nullable instancetype)classInfoWithClassName:(NSString *)className;

@end

NS_ASSUME_NONNULL_END




//YYClassInfo 是对于Class进行了封装，进行封装增加描述

//在这个类中，YY对于Ivar，property和Method都进行了一层封装，最后都服务于YYClassInfo，这样做的一个好处就是把原来里层的内容暴露在外层，方便查找，也可以进行缓存，提高访问效率和命中率，这也是对后面进行json转换做的一些工作



