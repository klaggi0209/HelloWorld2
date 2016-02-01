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
		$router->get('showcase', 'Showcase\Controllers\ContentController@landingPage');

		$router->get('showcase{spacer}a-{itemId}', 'Showcase\Controllers\ContentController@showItemView')
			->where('spacer','(/.+?/)|(/)')
			->where('itemId','[0-9]+');

		$router->get('showcase/navigation', 'Showcase\Controllers\ContentController@showCategory');

		// Showcase examples
		/*
		 * referred pages should extend 'templates.ExamplePage'.
		 * Each section should extend 'templates.Example'.
		 */
		$router->get('showcase/basics', 'Showcase\Controllers\ExampleController@showBasicExamples');

		$router->get('showcase/categories', 'Showcase\Controllers\ExampleController@showCategoryExamples');
		$router->get('showcase/categories/{level1}/{level2?}/{level3?}/{level4?}/{level5?}/{level6?}','Showcase\Controllers\ExampleController@showCategoryExamples');

		$router->get('showcase/items', 'Showcase\Controllers\ExampleController@showItemExamples');

		// Last route to define!
		$router->get('showcase/{level1}/{level2?}/{level3?}/{level4?}/{level5?}/{level6?}','Showcase\Controllers\ContentController@showCategory');
	}
}
