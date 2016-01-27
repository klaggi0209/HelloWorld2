(function($) {

    $(document).ready(function() {

        $('[data-scrollTo]').each(function(i, elem) {
            var $elem = $( elem );

            $elem.click( function( e ) {
                var selector = $elem.attr('data-scrollTo');
                var scrollOffset = parseInt( $elem.attr('data-scrollOffset') );
                var targetOffset;


                e.preventDefault();

                if( $.isNumeric( selector ) )
                {
                    targetOffset = parseInt( selector );
                }
                else
                {
                    targetOffset = $( selector ).offset().top;
                }

                $('html,body').animate({
                    scrollTop: (targetOffset - scrollOffset)
                }, 300);
            });
        });

    });

}(jQuery));