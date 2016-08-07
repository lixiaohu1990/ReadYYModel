//
//  AppDelegate.m
//  ModelBenchmark
//
//  Created by ibireme on 15/9/18.
//  Copyright (c) 2015 ibireme. All rights reserved.
//

#import "AppDelegate.h"

@interface AppDelegate ()
@end

@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
//    NSString *str = @"10.2345";
//    
//    NSRange range = NSMakeRange('.', 1);
//    NSString *a = [str substringWithRange:NSMakeRange('.', 1)];
//    
//    
//    NSLog(@"%@", a);
    
    NSCharacterSet *dot = [NSCharacterSet characterSetWithRange:NSMakeRange('.', 1)];
    NSRange range = [@"10.2345" rangeOfCharacterFromSet:dot];
    
    
    NSRange lcEnglishRange;
    NSCharacterSet *lcEnglishLetters;
    
    lcEnglishRange.location = (unsigned int)'a';
    lcEnglishRange.length = 26;
    lcEnglishLetters = [NSCharacterSet characterSetWithRange:lcEnglishRange];
    
    NSLog(@"%@", lcEnglishLetters);
//    
    
    return YES;
    
    
}
@end
