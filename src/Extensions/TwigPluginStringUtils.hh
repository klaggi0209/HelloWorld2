<?hh //strict

namespace Showcase\Extensions;

use Plenty\Plugin\Templates\Extensions\Twig_Extension;
use Plenty\Plugin\Templates\Extensions\Twig_SimpleFunction;
use Plenty\Plugin\Templates\Factories\TwigFactory;
use Plenty\Plugin\Application;

class TwigPluginStringUtils extends Twig_Extension
{
	public TwigFactory $factory;

	public function __construct(TwigFactory $factory)
	{
		$this->factory = $factory;
	}

	/**
	 * Returns the name of the extension.
	 *
	 * @return string The extension name
	 */
	public function getName():string
	{
		return 'Showcase_Extension_Plugin_StringUtils';
	}

  /**
   *
	 * @return array
   */
  public function getFunctions():array<Twig_SimpleFunction>
  {
		return [
			$this->factory->createSimpleFunction('number_format', [$this, 'numberFormat']),
		];
  }


	/**
	 * Format the given number with comma as decimal delimiter.
	 * The resulting string number has always two decimal digits.
	 *
	 * @param string $n	The number to be formated.
	 * @param integer		$m	The count of decimal digits. [optional, default=2]
	 *
	 * @return float|string
	 */
	public function numberFormat(string $n, ?int $m = 2):float
	{
		if(!is_null($m) && $m < 0)
		{
			$m = 0;
		}
		
		return number_format($n, $m, ',', '');
	}
}
