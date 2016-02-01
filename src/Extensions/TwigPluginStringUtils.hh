<?hh //strict

namespace Showcase\Extensions;

use Plenty\Plugin\Templates\Extensions\Twig_Extension;
use Plenty\Plugin\Templates\Extensions\Twig_SimpleFunction;
use Plenty\Plugin\Templates\Extensions\Twig_SimpleFilter;
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
	 * @return array
	 */
	public function getFilters():array<Twig_SimpleFilter>
	{
		return [
			$this->factory->createSimpleFilter('cssSelector', [$this, 'formatCssSelector']),
			$this->factory->createSimpleFilter('typeof', [$this, 'typeof']),
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

	/**
     * Convert the given string to a valid CSS selector.
     * @param string $in 	The unformatted input
     * @ return string 		a lower case css selector
     */
    public function formatCssSelector( string $in ):string
    {
    	// remove HTML-tags
    	$in = strip_tags( $in );

    	// transform to lower case string
		$in = strtolower( $in );

		// replace special characters
		$in = str_replace( 
			array( "ä", "ö", "ü", "Ä", "Ö", "Ü", "ß"), 
			array( "ae", "oe", "ue", "ae", "oe", "ue", "ss"),
			$in
		);

		// replace whitespaces
		$in = preg_replace( "/[\s]+/", "-", $in );

		// remove invalid characters
		$in = preg_replace( "/[^a-zA-Z0-9\-]/", "", $in );

		return $in;
    }

	public function typeof( string $in ):string
	{
		return gettype($in);
	}
}
