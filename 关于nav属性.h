
#pragma mark - 1.关于nav导航栏
1.隐藏导航栏上的返回字体
//Swift
UIBarButtonItem.appearance().setBackButtonTitlePositionAdjustment(UIOffsetMake(0, -60), forBarMetrics: .Default)
//OC
[[UIBarButtonItem appearance] setBackButtonTitlePositionAdjustment:UIOffsetMake(0, -60) forBarMetrics:UIBarMetricsDefault];


2.设置滑动的时候隐藏navigationbar
navigationController.hidesBarsOnSwipe = Yes

3.动态隐藏NavigationBar
//1.当我们的手离开屏幕时候隐藏
- (void)scrollViewWillEndDragging:(UIScrollView *)scrollView withVelocity:(CGPoint)velocity targetContentOffset:(inout CGPoint *)targetContentOffset
{
    if(velocity.y > 0)
    {
        [self.navigationController setNavigationBarHidden:YES animated:YES];
    } else {
        [self.navigationController setNavigationBarHidden:NO animated:YES];
    }
}
velocity.y这个量，在上滑和下滑时，变化极小（小数），但是因为方向不同，有正负之分，这就很好处理了。
//2.在滑动过程中隐藏
//像safari
(1)
self.navigationController.hidesBarsOnSwipe = YES;
(2)
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    CGFloat offsetY = scrollView.contentOffset.y + __tableView.contentInset.top;
    CGFloat panTranslationY = [scrollView.panGestureRecognizer translationInView:self.tableView].y;
    if (offsetY > 64) {
        if (panTranslationY > 0)
        {
            //下滑趋势，显示
            [self.navigationController setNavigationBarHidden:NO animated:YES];
        } else {
            //上滑趋势，隐藏
            [self.navigationController setNavigationBarHidden:YES animated:YES];
        }
    } else {
        [self.navigationController setNavigationBarHidden:NO animated:YES];
    }
}
这里的offsetY > 64只是为了在视图滑过navigationBar的高度之后才开始处理，防止影响展示效果。panTranslationY是scrollView的pan手势的手指位置的y值，可能不是太好，因为panTranslationY这个值在较小幅度上下滑动时，可能都为正或都为负，这就使得这一方式不太灵敏.

4.设置导航栏透明
//方法一:设置透明度
[[[self.navigationController.navigationBar subviews]objectAtIndex:0] setAlpha:0.1];
//方法二:设置背景图片
/**
 * 设置导航栏,使其透明
 *
 */
- (void)setNavigationBarColor:(UIColor *)color targetController:(UIViewController *)targetViewController{
    //导航条的颜色 以及隐藏导航条的颜色targetViewController.navigationController.navigationBar.shadowImage = [[UIImage alloc]init];
    CGRect rect=CGRectMake(0.0f, 0.0f, 1.0f, 1.0f); UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext(); CGContextSetFillColorWithColor(context, [color CGColor]); CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext(); UIGraphicsEndImageContext(); [targetViewController.navigationController.navigationBar setBackgroundImage:theImage forBarMetrics:UIBarMetricsDefault];
}

//第3种
//设置一张空的图片
[self.navigationController.navigationBar setBackgroundImage:[[UIImage alloc]init] forBarMetrics:UIBarMetricsDefault];
//清除边框，设置一张空的图片(隐藏底部阴影条，传递一个空图片的UIImage对象)
[self.navigationController.navigationBar setShadowImage:[[UIImage alloc]init]];
self.navigationController.navigationBar.translucent = YES;

5.修改状态栏字体颜色
只能设置两种颜色，黑色和白色，系统默认黑色
设置为白色方法：
（1）在plist里面添加Status bar style，值为UIStatusBarStyleLightContent（白色）或UIStatusBarStyleDefault（黑 色）
（2）在Info.plist中设置UIViewControllerBasedStatusBarAppearance 为NO

7.设置导航栏右边有2个按钮
UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithCustomView:view];
self.navigationItem.rightBarButtonItem = item;

系统默认的rightBarButtonItem边距
self.navigationItem.leftBarButtonItem.imageInsets = UIEdgeInsetsMake(0,-20,0,0);
self.navigationItem.rightBarButtonItem.imageInsets = UIEdgeInsetsMake(0,-10,0,10);

8.隐藏底部的工具条
(- (void)pushViewController:(UIViewController *)viewController animated:(BOOL)animated在这个方法中使用)
viewController.hidesBottomBarWhenPushed = YES;

9.## 解决导航控制器pop手势失效
self.interactivePopGestureRecognizer.delegate = self;

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    // 手势何时有效 : 当导航控制器的子控制器个数 > 1就有效
    return self.childViewControllers.count > 1;
}

10.
UITabBarController *tabBarVc = (UITabBarController *)self.window.rootViewController;
UINavigationController *nav = tabBarVc.selectedViewController;
[nav pushViewController:webView animated:YES];

//状态栏
[[UIApplication sharedApplication] setStatusBarStyle:UIStatusBarStyleLightContent];

标题颜色
self.navigationController.navigationBar.titleTextAttributes = @{NSForegroundColorAttributeName : [UIColor someColor]}


设置了导航条背景颜色，会导致按钮标题颜色改变，通过以下方法修改
导航栏子控件颜色
self.navigationController.navigationBar.tintColor = [UIColor someColor];

修改导航条背景颜色
self.navigationController.navigationBar.barTintColor = [UIColor colorWithHexString:@"#2295f2"];

11.关闭navigationController的滑动返回手势
self.navigationController.interactivePopGestureRecognizer.enabled = NO;

12.这行代码可以关闭半透明效果，但是会导致坐标0点移动。

[UINavigationBar appearance].translucent = NO;
关闭坐标0点移动

self.edgesForExtendedLayout = UIRectEdgeNone;

13.设置导航控制器标题的颜色和字体大小等
NSDictionary *attributes = [NSDictionary dictionaryWithObjectsAndKeys:
                            [UIColor whiteColor],NSForegroundColorAttributeName,
                            [UIFont systemFontOfSize:17],NSFontAttributeName,nil];
[self.navigationController.navigationBar setTitleTextAttributes:attributes];

14.去掉导航栏下面的黑线
[self.navigationController.navigationBar setBackgroundImage:[[UIImage alloc]init] forBarMetrics:UIBarMetricsDefault];
//清除边框，设置一张空的图片(隐藏底部阴影条，传递一个空图片的UIImage对象)
[self.navigationController.navigationBar setShadowImage:[[UIImage alloc]init]];
//让导航栏不透明
self.navigationController.navigationBar.translucent = NO;
self.navigationController.navigationBar.barTintColor =


15.navigationBar根据滑动距离的渐变色实现
//第一种
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    CGFloat offsetToShow = 200.0;//滑动多少就完全显示
    CGFloat alpha = 1 - (offsetToShow - scrollView.contentOffset.y) / offsetToShow;
    [[self.navigationController.navigationBar subviews] objectAtIndex:0].alpha = alpha;
}

//第二种
- (void)scrollViewDidScroll:(UIScrollView *)scrollView
{
    CGFloat offsetToShow = 200.0;
    CGFloat alpha = 1 - (offsetToShow - scrollView.contentOffset.y) / offsetToShow;
    
    [self.navigationController.navigationBar setShadowImage:[UIImage new]];
    [self.navigationController.navigationBar setBackgroundImage:[self imageWithColor:[[UIColor orangeColor]colorWithAlphaComponent:alpha]] forBarMetrics:UIBarMetricsDefault];
}

//生成一张纯色的图片
- (UIImage *)imageWithColor:(UIColor *)color
{
    CGRect rect = CGRectMake(0.0f, 0.0f, 1.0f, 1.0f);
    UIGraphicsBeginImageContext(rect.size);
    CGContextRef context = UIGraphicsGetCurrentContext();
    CGContextSetFillColorWithColor(context, [color CGColor]);
    CGContextFillRect(context, rect);
    UIImage *theImage = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    return theImage;
}

//14.使左边导航栏按钮位置更加左边一点
{
    UIView *left = [[UIView alloc] init];
    left.frame = CGRectMake(0, 0, 0, 1);
    UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithCustomView:left];
    
    //使导航栏按钮位置更加左边或者右边
    UIBarButtonItem *nagetiveSpacer = [[UIBarButtonItem alloc]initWithBarButtonSystemItem:UIBarButtonSystemItemFixedSpace target:nil action:nil];
    nagetiveSpacer.width = -40;//这个值可以根据自己需要自己调整
    
    self.navigationItem.leftBarButtonItems = @[nagetiveSpacer,item];
}


UIBarButtonItem *item = [[UIBarButtonItem alloc] initWithCustomView:back];
item.width = -20;

#pragma mark - 导航栏的隐藏显示问题(正确的姿势)
1.// 设置导航控制器的代理为self
self.navigationController.delegate = self;

2.<UINavigationControllerDelegate>

3.// 将要显示控制器
- (void)navigationController:(UINavigationController *)navigationController willShowViewController:(UIViewController *)viewController animated:(BOOL)animated {
    // 判断要显示的控制器是否是自己
    BOOL isShowHomePage = [viewController isKindOfClass:[self class]];
    
    [self.navigationController setNavigationBarHidden:isShowHomePage animated:YES];
}
