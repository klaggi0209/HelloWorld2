<?hh // strict
namespace Showcase\Providers;

use Plenty\Plugin\ServiceProvider;
use Plenty\Plugin\Templates\Twig;
use Showcase\Extensions\TwigPluginStringUtils;
use Showcase\Extensions\TwigPluginTwigEscaper;

class ShowcaseServiceProvider extends ServiceProvider
{
	public function register():void
	{
		$this->getApplication()->register(\Showcase\Providers\ShowcaseRestRouteServiceProvider::class);
		$this->getApplication()->register(\Showcase\Providers\ShowcaseApiRouteServiceProvider::class);
		$this->getApplication()->register(\Showcase\Providers\ShowcaseRouteServiceProvider::class);
	}

	public function boot(Twig $twig):void
	{
		$twig->addExtension('Twig_Extensions_Extension_Intl');
		$twig->addExtension(TwigPluginStringUtils::class);
	}
}
