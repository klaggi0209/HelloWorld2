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
        return $twig->render('PlentyPluginShowcase::content.LandingPage');
    }

    public function showBasicExamples( Twig $twig ):string
    {
        return $twig->render('PlentyPluginShowcase::content.basics');
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

    public function showBasketExamples(Twig $twig, ItemDataLayerRepositoryContract $itemRepository):string {


                    $itemColumns = [
                        'itemDescription' => [
                            'name1',
                            'description'
                        ],
                        'variationBase' => [
                            'availability',
                            'unitCombinationId'
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
                            'itemId' => 133
                        ],
                        'variationBase.isPrimary?' => []
                    ];


                    $itemParams = [
                        'language' => 'de'
                    ];


                    $currentItem = $itemRepository
                        ->search( $itemColumns, $itemFilter, $itemParams )
                        ->current();



                $templateData = array(
                    'currentItem' => $currentItem
                );

                return $twig->render('PlentyPluginShowcase::content.Basket', $templateData );
    }

}
