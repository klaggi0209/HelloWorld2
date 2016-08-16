<?hh //strict

namespace Showcase\Controllers;

use Plenty\Plugin\Controller;
use Plenty\Plugin\Templates\Twig;

use Plenty\Modules\Category\Contracts\CategoryRepository;
use Plenty\Modules\Item\DataLayer\Contracts\ItemDataLayerRepositoryContract;
use Plenty\Modules\Category\Models\Category;

class ContentController extends Controller
{
    public function showLandingPage(Twig $twig):string
    {
      $ch = curl_init();
      curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
      curl_setopt($ch,CURLOPT_USERAGENT,'plenty-plugin-showcase-fork-count');
      curl_setopt($ch, CURLOPT_URL, 'https://api.github.com/repos/plentymarkets/plenty-plugin-showcase');
      $result = curl_exec($ch);
      curl_close($ch);
      $payload = json_decode($result, true);
      $templateData = array(
          'curlResult' => $payload,
      );
      return $twig->render('PlentyPluginShowcase::content.LandingPage', $templateData);
    }

    public function showTutorialsHello( Twig $twig):string
    {
        return $twig->render('PlentyPluginShowcase::content.tutorials.helloworld');
    }
    public function showTutorialsTopsellers( Twig $twig):string
    {
        return $twig->render('PlentyPluginShowcase::content.tutorials.topsellers');
    }

    public function showDevGuidePage(Twig $twig, string $pageName):string
    {
        return $twig->render('PlentyPluginShowcase::content.devguide.' . $pageName);
    }

    public function showCategoryExamples(
        Twig $twig,
        CategoryRepository $categoryRepository,
        ItemDataLayerRepositoryContract $itemRepository,
        ?string $lvl1 = null,
        ?string $lvl2 = null,
        ?string $lvl3 = null,
        ?string $lvl4 = null,
        ?string $lvl5 = null,
        ?string $lvl6 = null
        ):string
    {
        $categoryList = $categoryRepository->getSitemapList('content');
        $categoryTree = $categoryRepository->getSitemapTree('item');

        $currentCategory = null;
        $currentCategoryItems = null;
        if( $lvl1 !== null )
        {
            $currentCategory = $categoryRepository->findCategoryByUrl( $lvl1, $lvl2, $lvl3, $lvl4, $lvl5, $lvl6 );


            $itemColumns = [
                'itemDescription' => [
                    'name1',
                    'shortDescription'
                ],
                'variationRetailPrice' => [
                    'price'
                ],
                'variationImageList' => [
                    'path'
                ]
            ];


            $itemFilter = [
                'variationBase.isPrimary?' => []
            ];

            /*
            $categoryFilter = $this->getCategoryFilter( $categoryRepository, $currentCategory );
            if( count($categoryFilter) )
            {
                $filter['variationCategory']
            }
            */

            $itemParams = [
                'language' => 'de'
            ];

            $currentCategoryItems = $itemRepository->search( $itemColumns, $itemFilter, $itemParams );
        }

        $templateData = array(
            'categoryList' => $categoryList,
            'categoryTree' => $categoryTree,
            'currentCategory' => $currentCategory,
            'categoryItems' => $currentCategoryItems
        );

        return $twig->render('PlentyPluginShowcase::content.categories', $templateData);
    }

    public function showItemExamples(Twig $twig, ItemDataLayerRepositoryContract $itemRepository, ?string $itemId = null):string
    {
        $currentItem = null;

        if( $itemId !== null )
        {
            $itemColumns = [
                'itemDescription' => [
                    'name1',
                    'description'
                ],
                'variationBase' => [
                    'availability'
                ],
                'variationRetailPrice' => [
                    'price'
                ],
                'variationImageList' => [
                    'path'
                ]
            ];


            $itemFilter = [
                'itemBase.hasId' => [
                    'itemId' => $itemId
                ],
                'variationBase.isPrimary?' => []
            ];


            $itemParams = [
                'language' => 'de'
            ];

            $currentItem = $itemRepository->search( $itemColumns, $itemFilter, $itemParams )->current();

        }

        $templateData = array(
            'currentItem' => $currentItem
        );

        return $twig->render('PlentyPluginShowcase::content.Items', $templateData );
    }
}
