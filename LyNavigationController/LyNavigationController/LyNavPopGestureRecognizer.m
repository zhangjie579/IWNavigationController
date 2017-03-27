//
//  LyNavPopGestureRecognizer.m
//  LyNavigationController
//
//  Created by 张杰 on 2017/3/27.
//  Copyright © 2017年 张杰. All rights reserved.
//

#import "LyNavPopGestureRecognizer.h"

@implementation LyNavPopGestureRecognizer

+ (void)removePopGestureRecognizer
{
    
    UIViewController *currentVc = [self topViewController];
    //移除系统默认的侧滑返回手势
    currentVc.navigationController.interactivePopGestureRecognizer.enabled = NO;
    
    //移除全屏侧滑返回手势
    id target = currentVc.navigationController.interactivePopGestureRecognizer.delegate;
    UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] initWithTarget:target action:nil];
    
    [currentVc.view addGestureRecognizer:pan];
}

+ (void)addPopGestureRecognizer
{
    UIViewController *currentVc = [self topViewController];
    currentVc.navigationController.interactivePopGestureRecognizer.enabled = YES;
    
    id target = currentVc.navigationController.interactivePopGestureRecognizer.delegate;
    UIPanGestureRecognizer *pan = [[UIPanGestureRecognizer alloc] initWithTarget:target action:@selector(handleNavigationTransition:)];
    [currentVc.view addGestureRecognizer:pan];
}

+ (UIViewController*)topViewController
{
    return [self topViewControllerWithRootViewController:[UIApplication sharedApplication].keyWindow.rootViewController];
}

+ (UIViewController*)topViewControllerWithRootViewController:(UIViewController*)rootViewController
{
    if ([rootViewController isKindOfClass:[UITabBarController class]]) {
        UITabBarController *tabBarController = (UITabBarController *)rootViewController;
        return [self topViewControllerWithRootViewController:tabBarController.selectedViewController];
    }
    else if ([rootViewController isKindOfClass:[UINavigationController class]]) {
        UINavigationController* navigationController = (UINavigationController*)rootViewController;
        return [self topViewControllerWithRootViewController:navigationController.visibleViewController];
    }
    else if (rootViewController.presentedViewController) {
        UIViewController* presentedViewController = rootViewController.presentedViewController;
        return [self topViewControllerWithRootViewController:presentedViewController];
    }
    else {
        return rootViewController;
    }
}


@end
