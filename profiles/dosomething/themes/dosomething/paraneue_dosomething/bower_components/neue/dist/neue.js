!function(){var e,n,t;!function(i){function o(e,n){return k.call(e,n)}function s(e,n){var t,i,o,s,a,r,l,c,u,d,f,p=n&&n.split("/"),m=w.map,h=m&&m["*"]||{};if(e&&"."===e.charAt(0))if(n){for(p=p.slice(0,p.length-1),e=e.split("/"),a=e.length-1,w.nodeIdCompat&&C.test(e[a])&&(e[a]=e[a].replace(C,"")),e=p.concat(e),u=0;u<e.length;u+=1)if(f=e[u],"."===f)e.splice(u,1),u-=1;else if(".."===f){if(1===u&&(".."===e[2]||".."===e[0]))break;u>0&&(e.splice(u-1,2),u-=2)}e=e.join("/")}else 0===e.indexOf("./")&&(e=e.substring(2));if((p||h)&&m){for(t=e.split("/"),u=t.length;u>0;u-=1){if(i=t.slice(0,u).join("/"),p)for(d=p.length;d>0;d-=1)if(o=m[p.slice(0,d).join("/")],o&&(o=o[i])){s=o,r=u;break}if(s)break;!l&&h&&h[i]&&(l=h[i],c=u)}!s&&l&&(s=l,r=c),s&&(t.splice(0,r,s),e=t.join("/"))}return e}function a(e,n){return function(){return p.apply(i,y.call(arguments,0).concat([e,n]))}}function r(e){return function(n){return s(n,e)}}function l(e){return function(n){v[e]=n}}function c(e){if(o(g,e)){var n=g[e];delete g[e],b[e]=!0,f.apply(i,n)}if(!o(v,e)&&!o(b,e))throw new Error("No "+e);return v[e]}function u(e){var n,t=e?e.indexOf("!"):-1;return t>-1&&(n=e.substring(0,t),e=e.substring(t+1,e.length)),[n,e]}function d(e){return function(){return w&&w.config&&w.config[e]||{}}}var f,p,m,h,v={},g={},w={},b={},k=Object.prototype.hasOwnProperty,y=[].slice,C=/\.js$/;m=function(e,n){var t,i=u(e),o=i[0];return e=i[1],o&&(o=s(o,n),t=c(o)),o?e=t&&t.normalize?t.normalize(e,r(n)):s(e,n):(e=s(e,n),i=u(e),o=i[0],e=i[1],o&&(t=c(o))),{f:o?o+"!"+e:e,n:e,pr:o,p:t}},h={require:function(e){return a(e)},exports:function(e){var n=v[e];return"undefined"!=typeof n?n:v[e]={}},module:function(e){return{id:e,uri:"",exports:v[e],config:d(e)}}},f=function(e,n,t,s){var r,u,d,f,p,w,k=[],y=typeof t;if(s=s||e,"undefined"===y||"function"===y){for(n=!n.length&&t.length?["require","exports","module"]:n,p=0;p<n.length;p+=1)if(f=m(n[p],s),u=f.f,"require"===u)k[p]=h.require(e);else if("exports"===u)k[p]=h.exports(e),w=!0;else if("module"===u)r=k[p]=h.module(e);else if(o(v,u)||o(g,u)||o(b,u))k[p]=c(u);else{if(!f.p)throw new Error(e+" missing "+u);f.p.load(f.n,a(s,!0),l(u),{}),k[p]=v[u]}d=t?t.apply(v[e],k):void 0,e&&(r&&r.exports!==i&&r.exports!==v[e]?v[e]=r.exports:d===i&&w||(v[e]=d))}else e&&(v[e]=t)},e=n=p=function(e,n,t,o,s){if("string"==typeof e)return h[e]?h[e](n):c(m(e,n).f);if(!e.splice){if(w=e,w.deps&&p(w.deps,w.callback),!n)return;n.splice?(e=n,n=t,t=null):e=i}return n=n||function(){},"function"==typeof t&&(t=o,o=s),o?f(i,e,n,t):setTimeout(function(){f(i,e,n,t)},4),p},p.config=function(e){return p(e)},e._defined=v,t=function(e,n,t){n.splice||(t=n,n=[]),o(v,e)||o(g,e)||(g[e]=[e,n,t])},t.amd={jQuery:!0}}(),t("../bower_components/almond/almond",function(){}),t("neue/carousel",[],function(){var e=window.jQuery;e(function(){function n(){0===o?o=s:o--}function t(){o===s?o=0:o++}function i(i){e("#slide"+o).removeClass("visible"),"prev"===i?n():t(),e("#slide"+o).addClass("visible")}e("#slide0").addClass("visible");var o=0,s=e(".slide").length-1,a=e("#prev, #next");a.click(function(){i(e(this).attr("id"))})})}),t("neue/events",[],function(){var e={},n=-1,t=function(n,t){return e[n]?(setTimeout(function(){for(var i=e[n],o=i?i.length:0;o--;)i[o].func(n,t)},0),!0):!1},i=function(t,i){e[t]||(e[t]=[]);var o=(++n).toString();return e[t].push({token:o,func:i}),o},o=function(n){for(var t in e)if(e[t])for(var i=0,o=e[t].length;o>i;i++)if(e[t][i].token===n)return e[t].splice(i,1),n;return!1};return{publish:t,subscribe:i,unsubscribe:o}}),t("neue/jump-scroll",[],function(){var e=window.jQuery;e(function(){e(".js-jump-scroll").on("click",function(n){n.preventDefault();var t=e(this).attr("href");e("html,body").animate({scrollTop:e(n.target.hash).offset().top},"slow",function(){window.location.hash=t})})})}),t("neue/media-selector",[],function(){var e=window.jQuery,n=function(t,i){if(void 0!==t&&e(t.length)){if(!this instanceof n)return new n(t,i);var o=this;i=i||{},o.cfg=i={fieldClassName:"string"==typeof i.fieldClassName?i.fieldClassName:"media-options",fieldSelector:"string"==typeof i.fieldSelector?i.fieldSelector:".form-type-radio",optionSelector:"string"==typeof i.optionSelector?i.optionSelector:"label"},o.$fieldGroup=e(t).addClass(o.cfg.fieldClassName),o.$checked=[],o.init()}};n.prototype={init:function(){var n=this,t=n.cfg;n.$fieldGroup.find(t.fieldSelector).each(function(i){var o=e(this),s=(i+1)%2===0?"-second":"-first";o.addClass(s),o.find("input[type='radio']:checked").length>0&&n.check(o),o.find(t.optionSelector).on("click",function(){n.$checked.length>0&&n.uncheck(n.$checked),n.check(o)})})},check:function(e){e.addClass("selected").find("input[type='radio']").attr("checked",!0),this.$checked=e},uncheck:function(e){e.removeClass("selected").find("input[type='radio']").attr("checked",!1)}},e(function(){e(".js-media-options").each(function(){new n(e(this))})})}),t("neue/menu",[],function(){var e=window.jQuery;e(function(){e(".js-toggle-mobile-menu").on("click",function(){e(".chrome--nav").toggleClass("is-visible")}),e(".js-footer-col").addClass("is-collapsed"),e(".js-footer-col h4").on("click",function(){window.matchMedia("screen and (max-width: 768px)").matches&&e(this).closest(".js-footer-col").toggleClass("is-collapsed")})})}),t("neue/messages",[],function(){var e=window.jQuery,n='<a href="#" class="js-close-message message-close-button white">×</a>',t=function(t,i){t.append(n),t.on("click",".js-close-message",function(n){n.preventDefault(),e(this).parent(".messages").slideUp(),i&&"function"==typeof i&&i()})};return e(function(){t(e(".messages"))}),{attachCloseButton:t}}),t("neue/modal",["require","./events"],function(e){var n=window.jQuery,t=window.Modernizr,i=e("./events"),o=!1,s=null,a=n(document),r=n(".chrome"),l=null,c=n("<a href='#' class='js-close-modal js-modal-generated modal-close-button -alt'>skip</a>"),u=n("<a href='#' class='js-close-modal js-modal-generated modal-close-button'>&#215;</a>"),d=null,f=!1,p=function(){return null!==d},m=function(e,t,i){switch(t){case"skip":e.prepend(c),c.on("click",function(e){e.preventDefault(),n(i).submit()}),f=!1;break;case"false":case"0":f=!1;break;default:e.prepend(u),f=!0}},h=function(e,n){if(n=n||{},n.animated="boolean"==typeof n.animated?n.animated:!0,n.closeButton="undefined"!=typeof n.closeButton?n.closeButton:e.attr("data-modal-close"),n.skipForm="undefined"!=typeof n.skipForm?n.skipForm:e.attr("data-modal-skip-form"),0===e.length)return!1;if(!o)return s={$el:e,options:n},!1;var c="-"+a.scrollTop()+"px";m(e,n.closeButton,n.skipForm),p()?(d.hide(),e.show()):(r.css("top",c),r.addClass("modal-open"),l.css("display","block"),n.animated&&t.cssanimations&&l.addClass("animated-open"),e.css("display","block")),setTimeout(function(){a.scrollTop(0)},50),i.publish("Modal:Open",e),d=e},v=function(e){l.css("display","none"),l.removeClass("animated-close"),d.css("display","none"),d.find(".js-modal-generated").remove(),r.removeClass("modal-open"),r.css("top",""),a.scrollTop(e),d=null},g=function(e){e=e||{},e.animated="undefined"!=typeof e.animated?e.animated:!0;var n=-1*parseInt(r.css("top"));e.animated&&t.cssanimations?(l.addClass("animated-close"),l.one("webkitAnimationEnd oanimationend msAnimationEnd animationend",function(){v(n)})):v(n),window.location.hash==="#"+d.attr("id")&&(window.location.hash="/"),i.publish("Modal:Close",d)},w=function(e){e.preventDefault();var t=n(this).data("modal-href");h(n(t))},b=function(e){e.target===this&&(n(this).hasClass("js-close-modal")||f)&&(e.preventDefault(),g())};return a.ready(function(){var e=n("body");l=n("<div class='modal-container'></div>"),e.append(l),n("[data-modal]").each(function(){n(this).appendTo(l),n(this).attr("hidden",!0)});var t=window.location.hash;t&&"#/"!==t&&n(t)&&"undefined"!=typeof n(t).data("modal")&&h(n(t)),o=!0,null!==s&&h(s.$el,s.options),e.on("click","[data-modal-href]",w),e.on("click",".modal-container",b),e.on("click",".js-close-modal",b)}),{isOpen:p,open:h,close:g}}),t("neue/scroll-indicator",[],function(){function e(e,n,t){for(var i=0,o=e?e.length:i;o>i;){var s=i+o>>>1;e[s][t]<n?i=s+1:o=s}return i?i-1:i}function n(n,t){var i=e(n,t,"offset");return n[i]}function t(e){var n=a(e.attr("href"));n.length&&r.push({offset:n.offset().top,link:e})}function i(){r=[],a(".js-scroll-indicator").find("a").each(function(e,n){t(a(n))})}function o(){var e=n(r,a(window).scrollTop()+40),t=e.link.parentsUntil(".js-scroll-indicator"),i=a();s&&s!==e&&(s.link.removeClass("is-active"),i=s.link.parentsUntil(".js-scroll-indicator")),e.link.addClass("is-active"),t.addClass("is-active"),i.not(t).removeClass("is-active"),s=e}var s,a=window.jQuery,r=[],l=function(e,n,t){var i,o,s,a=null,r=0;t||(t={});var l=function(){r=new Date,a=null,s=e.apply(i,o)};return function(){var c=new Date;r||t.leading!==!1||(r=c);var u=n-(c-r);return i=this,o=arguments,0>=u?(clearTimeout(a),a=null,r=c,s=e.apply(i,o)):a||t.trailing===!1||(a=setTimeout(l,u)),s}};a(function(){i();var e=l(o,60);a(window).on("scroll",e),a(window).on("resize",i)})}),t("neue/sticky",[],function(){function e(){o=[],i(".js-sticky").each(function(e,t){n(t)})}function n(e){var n=i(e).offset().top,s={$el:i(e),offset:n};o.push(s),t()}function t(){i.each(o,function(e,n){i(window).scrollTop()>n.offset?n.$el.addClass("is-stuck"):n.$el.removeClass("is-stuck")})}var i=window.jQuery,o=[];i(function(){e(),i(window).on("scroll",t),i(window).on("resize",e)})}),t("neue/validation",["require","./events"],function(e){var n=window.jQuery,t=e("./events"),i=[],o=function(e){e.each(function(){var e=n(this);s(n("label[for='"+e.attr("id")+"']")),e.on("blur",function(n){n.preventDefault(),a(e)})})},s=function(e){if(0===e.find(".inner-label").length){var t=n("<div class='inner-label'></div>");t.append("<div class='label'>"+e.html()+"</div>"),t.append("<div class='message'></div>"),e.html(t)}},a=function(e,t,o){t="undefined"!=typeof t?t:!1,o="undefined"!=typeof o?o:function(e,n){c(e,n)};var s=e.data("validate"),r=e.data("validate-trigger");if(r&&a(n(r)),!i[s])return void console.error("A validation with the name "+s+" has not been registered.");if(f(e)){var l=e.val();if(t||""!==l)if("match"===s){var u=n(e.data("validate-match")).val();i[s].fn(l,u,function(n){o(e,n)})}else i[s].fn(l,function(n){o(e,n)})}else if("match"===s){var d=n(e.data("validate-match"));i[s].fn(e,d,function(n){o(e,n)})}else i[s].fn(e,function(n){o(e,n)})},r=function(e,n){if(i[e])throw"A validation function with that name has already been registered";i[e]=n},l=function(e,n){var t={fn:n};r(e,t)},c=function(e,i){var o,s=n("label[for='"+e.attr("id")+"']"),a=s.find(".message"),r=s.height();return e.removeClass("success error warning shake"),a.removeClass("success error warning"),i.success===!0?(e.addClass("success"),a.addClass("success")):(e.addClass("error"),a.addClass("error"),f(e)&&e.addClass("shake"),t.publish("Validation:InlineError",s.attr("for"))),i.message&&a.text(i.message),i.suggestion&&(a.html("Did you mean "+i.suggestion.full+"? <a href='#' data-suggestion='"+i.suggestion.full+"'class='js-mailcheck-fix'>Fix it!</a>"),t.publish("Validation:Suggestion",i.suggestion.domain)),o=a.height(),o>r?s.css("height",o+"px"):s.css("height",""),s.addClass("show-message"),n(".js-mailcheck-fix").on("click",function(e){e.preventDefault();var i=n("#"+n(this).closest("label").attr("for"));i.val(n(this).data("suggestion")),i.trigger("blur"),t.publish("Validation:SuggestionUsed",n(this).text())}),e.on("focus",function(){e.removeClass("warning error success shake"),s.removeClass("show-message"),s.css("height","")}),i.success},u=function(e){var n=e.find(":submit");n.attr("disabled",!0),n.addClass("loading"),"BUTTON"===n.prop("tagName")&&n.addClass("loading")},d=function(e){var n=e.find(":submit");n.attr("disabled",!1),n.removeClass("loading disabled")},f=function(e){var n=e.prop("tagName");return"INPUT"===n||"SELECT"===n||"TEXTAREA"===n};return n("body").on("submit","form",function(e,i){var o=n(this),s=o.find("[data-validate]");if(u(o),s=s.map(function(){var e=n(this);return"undefined"!=typeof e.attr("data-validate-required")||""!==e.val()?e:void 0}),0===s.length)return!0;if(i===!0)return!0;e.preventDefault();var r=0,l=0,f=!1;return s.each(function(){a(n(this),!0,function(e,i){r++,c(e,i),i.success&&l++,f||i.success!==!1||(f=!0,n("html,body").animate({scrollTop:e.offset().top-32},200)),r===s.length&&(l===s.length?(t.publish("Validation:Submitted",n(this).attr("id")),o.trigger("submit",!0)):(t.publish("Validation:SubmitError",n(this).attr("id")),d(o)))})}),!1}),l("match",function(e,n,t){return t(e===n&&""!==e?{success:!0,message:"Looks good!"}:{success:!1,message:"That doesn't match."})}),n(function(){o(n("body").find("[data-validate]"))}),{prepareFields:o,registerValidation:r,registerValidationFunction:l,validateField:a,showValidationMessage:c,Validations:i}}),t("neue/main",["require","./carousel","./events","./jump-scroll","./media-selector","./menu","./messages","./modal","./scroll-indicator","./sticky","./validation"],function(e){return window.NEUE={Carousel:e("./carousel"),Events:e("./events"),JumpScroll:e("./jump-scroll"),MediaSelector:e("./media-selector"),Menu:e("./menu"),Messages:e("./messages"),Modal:e("./modal"),ScrollIndicator:e("./scroll-indicator"),Sticky:e("./sticky"),Validation:e("./validation")},window.NEUE}),n(["neue/main"])}();
//# sourceMappingURL=neue.js.map