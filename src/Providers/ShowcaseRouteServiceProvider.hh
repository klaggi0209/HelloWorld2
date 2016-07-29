<?hh // strict
namespace Showcase\Providers;

use Plenty\Plugin\RouteServiceProvider;
use Plenty\Plugin\Routing\Router;
use Plenty\Plugin\Templates\Twig;
use Showcase\Extensions\TwigPluginStringUtils;

class ShowcaseRouteServiceProvider extends RouteServiceProvider
{
	/**
	 *
	 */
	public function register():void
	{
	}

	/**
	 *
	 */
	public function map(Router $router):void
	{
		$router->get('', 'Showcase\Controllers\ContentController@showLandingPage');
		$router->get('helloworld', 'Showcase\Controllers\ContentController@showTutorialsHello');
		$router->get('topsellers', 'Showcase\Controllers\ContentController@showTutorialsTopsellers');

		$router->get('dev-doc/{devGuidePage}', 'Showcase\Controllers\ContentController@showDevGuidePage');
		$router->get('categories', 'Showcase\Controllers\ContentController@showCategoryExamples');
		$router->get('categories/{level1}/{level2?}/{level3?}/{level4?}/{level5?}/{level6?}','Showcase\Controllers\ContentController@showCategoryExamples');

		$router->get('items', 'Showcase\Controllers\ContentController@showItemExamples');
        $router->get('items/item-{itemId}', 'Showcase\Controllers\ContentController@showItemExamples');
	}
}
