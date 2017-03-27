//
//  LyNavPopGestureRecognizer.h
//  LyNavigationController
//
//  Created by 张杰 on 2017/3/27.
//  Copyright © 2017年 张杰. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface LyNavPopGestureRecognizer : NSObject

#pragma mark - 如果移除在,viewWillAppear中remove,在viewWillDisappear中add,来保证其他页面正常
//移除侧滑返回手势
+ (void)removePopGestureRecognizer;

//添加侧滑返回手势
+ (void)addPopGestureRecognizer;

@end
