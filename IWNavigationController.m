//
//  IWNavigationController.m
//  zzy
//
//  Created by 张杰 on 2017/1/7.
//  Copyright © 2017年 黄江昆. All rights reserved.
//

#import "IWNavigationController.h"

@interface IWNavigationController ()

@end

@implementation IWNavigationController

+(void)initialize
{
    // 1.设置导航栏主题
    [self setupNavBarTheme];
    
    // 2.设置导航栏按钮主题
    [self setupBarButtonItemTheme];
}

/**
 *  设置导航栏按钮主题
 */
+ (void)setupBarButtonItemTheme
{
    UIBarButtonItem *item = [UIBarButtonItem appearance];
    
//    // 设置背景
//    [item setBackgroundImage:[UIImage imageNamed:@"navigationbar_button_background"] forState:UIControlStateNormal barMetrics:UIBarMetricsDefault];
//    [item setBackgroundImage:[UIImage imageNamed:@"navigationbar_button_background_pushed"] forState:UIControlStateHighlighted barMetrics:UIBarMetricsDefault];
//    [item setBackgroundImage:[UIImage imageNamed:@"navigationbar_button_background_disable"] forState:UIControlStateDisabled barMetrics:UIBarMetricsDefault];
    
    // 设置文字属性
    NSMutableDictionary *textAttrs = [NSMutableDictionary dictionary];
    textAttrs[NSForegroundColorAttributeName] = [UIColor whiteColor];
    textAttrs[UITextAttributeTextShadowOffset] = [NSValue valueWithUIOffset:UIOffsetZero];
    textAttrs[NSFontAttributeName] = [UIFont systemFontOfSize:16];
    
    //正常状态下
    [item setTitleTextAttributes:textAttrs forState:UIControlStateNormal];
    
    //高亮状态下
    [item setTitleTextAttributes:textAttrs forState:UIControlStateHighlighted];
    
    NSMutableDictionary *disableTextAttrs = [NSMutableDictionary dictionary];
    disableTextAttrs[NSForegroundColorAttributeName] =  [UIColor lightGrayColor];
    
    //失效状态下
    [item setTitleTextAttributes:disableTextAttrs forState:UIControlStateDisabled];
}

/**
 *  设置导航栏主题
 */
+ (void)setupNavBarTheme
{
    // 取出appearance对象
    UINavigationBar *navBar = [UINavigationBar appearance];
    
#warning 注意:setBackgroundImage和setShadowImage就能去掉导航栏底部的黑线
    // 设置背景
    [navBar setBackgroundImage:[CornerSettingHelp createImageWithColor:[UIColor colorWithRed:52/255.0 green:157/255.0 blue:246/255.0 alpha:1]] forBarMetrics:UIBarMetricsDefault];
    [UIApplication sharedApplication].statusBarStyle = UIStatusBarStyleLightContent;
    
    //清除边框，设置一张空的图片(隐藏底部阴影条，传递一个空图片的UIImage对象)
    [navBar setShadowImage:[[UIImage alloc]init]];
    
    //设置导航栏的背景颜色
//    navBar.barTintColor = ColorBackgroundNav;
    
    // 设置标题属性
    NSMutableDictionary *textAttrs = [NSMutableDictionary dictionary];
    textAttrs[NSForegroundColorAttributeName] = [UIColor blackColor];
    textAttrs[UITextAttributeTextShadowOffset] = [NSValue valueWithUIOffset:UIOffsetZero];
    textAttrs[NSFontAttributeName] = [UIFont boldSystemFontOfSize:19];
    [navBar setTitleTextAttributes:textAttrs];
}

-(void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated
{
    if (self.viewControllers.count > 0) {
        viewController.hidesBottomBarWhenPushed = YES;
//        viewController.navigationItem.leftBarButtonItem = [self itemWithIcon:@"navigationbar_back" highIcon:@"navigationbar_back_highlighted" target:self action:@selector(back)];
//        viewController.navigationItem.rightBarButtonItem = [self itemWithIcon:@"navigationbar_more" highIcon:@"navigationbar_more_highlighted" target:self action:@selector(more)];
        
        
    }
    [super pushViewController:viewController animated:animated];
}

- (void)more
{
    [self popToRootViewControllerAnimated:YES];
}

- (void)back
{
    [self popViewControllerAnimated:YES];
}

- (UIBarButtonItem *)itemWithIcon:(NSString *)icon highIcon:(NSString *)highIcon target:(id)target action:(SEL)action
{
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button setBackgroundImage:[UIImage imageNamed:icon] forState:UIControlStateNormal];
    [button setBackgroundImage:[UIImage imageNamed:highIcon] forState:UIControlStateHighlighted];
    button.frame = (CGRect){CGPointZero, button.currentBackgroundImage.size};
    [button addTarget:target action:action forControlEvents:UIControlEventTouchUpInside];
    return [[UIBarButtonItem alloc] initWithCustomView:button];
}

@end
