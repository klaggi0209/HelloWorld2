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
		$router->get('showcase', 'Showcase\Controllers\ContentController@showLandingPage');


		$router->get('showcase/basics', 'Showcase\Controllers\ContentController@showBasicExamples');

		$router->get('showcase/categories', 'Showcase\Controllers\ContentController@showCategoryExamples');
		$router->get('showcase/categories/{level1}/{level2?}/{level3?}/{level4?}/{level5?}/{level6?}','Showcase\Controllers\ContentController@showCategoryExamples');

		$router->get('showcase/items', 'Showcase\Controllers\ContentController@showItemExamples');
	}
}
