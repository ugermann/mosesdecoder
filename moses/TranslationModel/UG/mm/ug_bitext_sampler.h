



<!DOCTYPE html>
<html lang="en" class="">
  <head prefix="og: http://ogp.me/ns# fb: http://ogp.me/ns/fb# object: http://ogp.me/ns/object# article: http://ogp.me/ns/article# profile: http://ogp.me/ns/profile#">
    <meta charset='utf-8'>

    <link crossorigin="anonymous" href="https://assets-cdn.github.com/assets/frameworks-2d635ad8ba43f32e07aa1fd713d692eff9a2e78dcd63daa5b580c38b36df3fdb.css" media="all" rel="stylesheet" />
    <link crossorigin="anonymous" href="https://assets-cdn.github.com/assets/github-79614139b0ee6e0bd515d6289eb56d63846e3bcff3e4ea798402e75e670d10be.css" media="all" rel="stylesheet" />
    
    
    

    <link as="script" href="https://assets-cdn.github.com/assets/frameworks-e677f2022a5d36e8f5ad35d0fcb01f83f1cdb613eda0449f533197693bcc6bda.js" rel="preload" />
    <link as="script" href="https://assets-cdn.github.com/assets/github-49c0de53df0e1f0dfaa632dcbe0daafc2222a8021741cedf015685977e77c100.js" rel="preload" />

    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta http-equiv="Content-Language" content="en">
    <meta name="viewport" content="width=1020">
    
    
    <title>mosesdecoder/ug_bitext_sampler.h at mmt-dev · ModernMT/mosesdecoder · GitHub</title>
    <link rel="search" type="application/opensearchdescription+xml" href="/opensearch.xml" title="GitHub">
    <link rel="fluid-icon" href="https://github.com/fluidicon.png" title="GitHub">
    <link rel="apple-touch-icon" href="/apple-touch-icon.png">
    <link rel="apple-touch-icon" sizes="57x57" href="/apple-touch-icon-57x57.png">
    <link rel="apple-touch-icon" sizes="60x60" href="/apple-touch-icon-60x60.png">
    <link rel="apple-touch-icon" sizes="72x72" href="/apple-touch-icon-72x72.png">
    <link rel="apple-touch-icon" sizes="76x76" href="/apple-touch-icon-76x76.png">
    <link rel="apple-touch-icon" sizes="114x114" href="/apple-touch-icon-114x114.png">
    <link rel="apple-touch-icon" sizes="120x120" href="/apple-touch-icon-120x120.png">
    <link rel="apple-touch-icon" sizes="144x144" href="/apple-touch-icon-144x144.png">
    <link rel="apple-touch-icon" sizes="152x152" href="/apple-touch-icon-152x152.png">
    <link rel="apple-touch-icon" sizes="180x180" href="/apple-touch-icon-180x180.png">
    <meta property="fb:app_id" content="1401488693436528">

      <meta content="https://avatars1.githubusercontent.com/u/10453592?v=3&amp;s=400" name="twitter:image:src" /><meta content="@github" name="twitter:site" /><meta content="summary" name="twitter:card" /><meta content="ModernMT/mosesdecoder" name="twitter:title" /><meta content="mosesdecoder - Moses, the machine translation system" name="twitter:description" />
      <meta content="https://avatars1.githubusercontent.com/u/10453592?v=3&amp;s=400" property="og:image" /><meta content="GitHub" property="og:site_name" /><meta content="object" property="og:type" /><meta content="ModernMT/mosesdecoder" property="og:title" /><meta content="https://github.com/ModernMT/mosesdecoder" property="og:url" /><meta content="mosesdecoder - Moses, the machine translation system" property="og:description" />
      <meta name="browser-stats-url" content="https://api.github.com/_private/browser/stats">
    <meta name="browser-errors-url" content="https://api.github.com/_private/browser/errors">
    <link rel="assets" href="https://assets-cdn.github.com/">
    
    <meta name="pjax-timeout" content="1000">
    

    <meta name="msapplication-TileImage" content="/windows-tile.png">
    <meta name="msapplication-TileColor" content="#ffffff">
    <meta name="selected-link" value="repo_source" data-pjax-transient>

    <meta name="google-site-verification" content="KT5gs8h0wvaagLKAVWq8bbeNwnZZK1r1XQysX3xurLU">
<meta name="google-site-verification" content="ZzhVyEFwb7w3e0-uOTltm8Jsck2F5StVihD0exw2fsA">
    <meta name="google-analytics" content="UA-3769691-2">

<meta content="collector.githubapp.com" name="octolytics-host" /><meta content="github" name="octolytics-app-id" /><meta content="3424A841:0FB9:8523F00:56E6A1DF" name="octolytics-dimension-request_id" />
<meta content="/&lt;user-name&gt;/&lt;repo-name&gt;/blob/show" data-pjax-transient="true" name="analytics-location" />



  <meta class="js-ga-set" name="dimension1" content="Logged Out">



        <meta name="hostname" content="github.com">
    <meta name="user-login" content="">

        <meta name="expected-hostname" content="github.com">
      <meta name="js-proxy-site-detection-payload" content="NjBlNWUxNDZhMWMzNWFiODEzZjg0ZmYyN2JkOGNiZjFiNjJjZTg3ZGM1ZjVlZGVkNjM5NjBhOGM4Mzc4OWRhNnx7InJlbW90ZV9hZGRyZXNzIjoiNTIuMzYuMTY4LjY1IiwicmVxdWVzdF9pZCI6IjM0MjRBODQxOjBGQjk6ODUyM0YwMDo1NkU2QTFERiJ9">

      <link rel="mask-icon" href="https://assets-cdn.github.com/pinned-octocat.svg" color="#4078c0">
      <link rel="icon" type="image/x-icon" href="https://assets-cdn.github.com/favicon.ico">

    <meta content="6a1643d2886aec81ce0185730afe7c7ce49ead47" name="form-nonce" />

    <meta http-equiv="x-pjax-version" content="84b73df4cd31dd50aab58ec7e7486f7d">
    

      
  <meta name="description" content="mosesdecoder - Moses, the machine translation system">
  <meta name="go-import" content="github.com/ModernMT/mosesdecoder git https://github.com/ModernMT/mosesdecoder.git">

  <meta content="10453592" name="octolytics-dimension-user_id" /><meta content="ModernMT" name="octolytics-dimension-user_login" /><meta content="37842250" name="octolytics-dimension-repository_id" /><meta content="ModernMT/mosesdecoder" name="octolytics-dimension-repository_nwo" /><meta content="true" name="octolytics-dimension-repository_public" /><meta content="true" name="octolytics-dimension-repository_is_fork" /><meta content="2236146" name="octolytics-dimension-repository_parent_id" /><meta content="moses-smt/mosesdecoder" name="octolytics-dimension-repository_parent_nwo" /><meta content="2236146" name="octolytics-dimension-repository_network_root_id" /><meta content="moses-smt/mosesdecoder" name="octolytics-dimension-repository_network_root_nwo" />
  <link href="https://github.com/ModernMT/mosesdecoder/commits/mmt-dev.atom" rel="alternate" title="Recent Commits to mosesdecoder:mmt-dev" type="application/atom+xml">


      <link rel="canonical" href="https://github.com/ModernMT/mosesdecoder/blob/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h" data-pjax-transient>
  </head>


  <body class="logged_out   env-production  vis-public fork page-blob">
    <a href="#start-of-content" tabindex="1" class="accessibility-aid js-skip-to-content">Skip to content</a>

    
    
    



      
      <div class="header header-logged-out" role="banner">
  <div class="container clearfix">

    <a class="header-logo-wordmark" href="https://github.com/" data-ga-click="(Logged out) Header, go to homepage, icon:logo-wordmark">
      <svg aria-hidden="true" class="octicon octicon-logo-github" height="28" role="img" version="1.1" viewBox="0 0 45 16" width="78"><path d="M8.64 5.19H4.88c-0.11 0-0.19 0.08-0.19 0.17v1.84c0 0.09 0.08 0.17 0.19 0.17h1.47v2.3s-0.33 0.11-1.25 0.11c-1.08 0-2.58-0.39-2.58-3.7s1.58-3.73 3.05-3.73c1.27 0 1.81 0.22 2.17 0.33 0.11 0.03 0.2-0.08 0.2-0.17l0.42-1.78c0-0.05-0.02-0.09-0.06-0.14-0.14-0.09-1.02-0.58-3.2-0.58C2.58 0 0 1.06 0 6.2s2.95 5.92 5.44 5.92c2.06 0 3.31-0.89 3.31-0.89 0.05-0.02 0.06-0.09 0.06-0.13V5.36c0-0.09-0.08-0.17-0.19-0.17h0.02zM27.7 0.44h-2.13c-0.09 0-0.17 0.08-0.17 0.17v4.09h-3.31V0.61c0-0.09-0.08-0.17-0.17-0.17h-2.13c-0.09 0-0.17 0.08-0.17 0.17v11.11c0 0.09 0.09 0.17 0.17 0.17h2.13c0.09 0 0.17-0.08 0.17-0.17V6.97h3.31l-0.02 4.75c0 0.09 0.08 0.17 0.17 0.17h2.13c0.09 0 0.17-0.08 0.17-0.17V0.61c0-0.09-0.08-0.17-0.17-0.17h0.02zM11.19 0.69c-0.77 0-1.38 0.61-1.38 1.38s0.61 1.38 1.38 1.38c0.75 0 1.36-0.61 1.36-1.38s-0.61-1.38-1.36-1.38z m1.22 3.55c0-0.09-0.08-0.17-0.17-0.17H10.11c-0.09 0-0.17 0.09-0.17 0.2 0 0 0 6.17 0 7.34 0 0.2 0.13 0.27 0.3 0.27 0 0 0.91 0 1.92 0 0.2 0 0.25-0.09 0.25-0.27 0-0.39 0-7.36 0-7.36v-0.02z m23.52-0.16h-2.09c-0.11 0-0.17 0.08-0.17 0.19v5.44s-0.55 0.39-1.3 0.39-0.97-0.34-0.97-1.09c0-0.73 0-4.75 0-4.75 0-0.09-0.08-0.17-0.17-0.17h-2.14c-0.09 0-0.17 0.08-0.17 0.17 0 0 0 2.91 0 5.11s1.23 2.75 2.92 2.75c1.39 0 2.52-0.77 2.52-0.77s0.05 0.39 0.08 0.45c0.02 0.05 0.09 0.09 0.16 0.09h1.34c0.11 0 0.17-0.08 0.17-0.17l0.02-7.47c0-0.09-0.08-0.17-0.19-0.17z m5.77-0.25c-1.2 0-2.02 0.53-2.02 0.53V0.59c0-0.09-0.08-0.17-0.17-0.17h-2.13c-0.09 0-0.17 0.08-0.17 0.17l-0.02 11.11c0 0.09 0.09 0.17 0.19 0.17h1.48c0.06 0 0.11-0.02 0.14-0.08 0.05-0.06 0.09-0.52 0.09-0.52s0.88 0.83 2.52 0.83c1.94 0 3.05-0.98 3.05-4.41s-1.77-3.88-2.97-3.88z m-0.83 6.27c-0.73-0.02-1.22-0.36-1.22-0.36V6.22s0.48-0.3 1.08-0.34c0.77-0.08 1.5 0.16 1.5 1.97 0 1.91-0.33 2.28-1.36 2.25z m-22.33-0.05c-0.09 0-0.33 0.05-0.58 0.05-0.78 0-1.05-0.36-1.05-0.83s0-3.13 0-3.13h1.59c0.09 0 0.16-0.08 0.16-0.19V4.25c0-0.09-0.08-0.17-0.16-0.17h-1.59V1.97c0-0.08-0.05-0.13-0.14-0.13H14.61c-0.09 0-0.14 0.05-0.14 0.13v2.17s-1.09 0.27-1.16 0.28c-0.08 0.02-0.13 0.09-0.13 0.17v1.36c0 0.11 0.08 0.19 0.17 0.19h1.11s0 1.44 0 3.28c0 2.44 1.7 2.69 2.86 2.69 0.53 0 1.17-0.17 1.27-0.22 0.06-0.02 0.09-0.09 0.09-0.16v-1.5c0-0.11-0.08-0.19-0.17-0.19h0.02z"></path></svg>
    </a>

    <div class="header-actions" role="navigation">
        <a class="btn btn-primary" href="/join?source=header-repo" data-ga-click="(Logged out) Header, clicked Sign up, text:sign-up">Sign up</a>
      <a class="btn" href="/login?return_to=%2FModernMT%2Fmosesdecoder%2Fblob%2Fmmt-dev%2Fmoses%2FTranslationModel%2FUG%2Fmm%2Fug_bitext_sampler.h" data-ga-click="(Logged out) Header, clicked Sign in, text:sign-in">Sign in</a>
    </div>

    <div class="site-search repo-scope js-site-search" role="search">
      <!-- </textarea> --><!-- '"` --><form accept-charset="UTF-8" action="/ModernMT/mosesdecoder/search" class="js-site-search-form" data-global-search-url="/search" data-repo-search-url="/ModernMT/mosesdecoder/search" method="get"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /></div>
  <label class="js-chromeless-input-container form-control">
    <div class="scope-badge">This repository</div>
    <input type="text"
      class="js-site-search-focus js-site-search-field is-clearable chromeless-input"
      data-hotkey="s"
      name="q"
      placeholder="Search"
      aria-label="Search this repository"
      data-global-scope-placeholder="Search GitHub"
      data-repo-scope-placeholder="Search"
      tabindex="1"
      autocapitalize="off">
  </label>
</form>
    </div>

      <ul class="header-nav left" role="navigation">
          <li class="header-nav-item">
            <a class="header-nav-link" href="/explore" data-ga-click="(Logged out) Header, go to explore, text:explore">Explore</a>
          </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="/features" data-ga-click="(Logged out) Header, go to features, text:features">Features</a>
          </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="https://enterprise.github.com/" data-ga-click="(Logged out) Header, go to enterprise, text:enterprise">Enterprise</a>
          </li>
          <li class="header-nav-item">
            <a class="header-nav-link" href="/pricing" data-ga-click="(Logged out) Header, go to pricing, text:pricing">Pricing</a>
          </li>
      </ul>

  </div>
</div>



    <div id="start-of-content" class="accessibility-aid"></div>

      <div id="js-flash-container">
</div>


    <div role="main" class="main-content">
        <div itemscope itemtype="http://schema.org/SoftwareSourceCode">
    <div id="js-repo-pjax-container" class="context-loader-container js-repo-nav-next" data-pjax-container>
      
<div class="pagehead repohead instapaper_ignore readability-menu experiment-repo-nav">
  <div class="container repohead-details-container">

    

<ul class="pagehead-actions">

  <li>
      <a href="/login?return_to=%2FModernMT%2Fmosesdecoder"
    class="btn btn-sm btn-with-count tooltipped tooltipped-n"
    aria-label="You must be signed in to watch a repository" rel="nofollow">
    <svg aria-hidden="true" class="octicon octicon-eye" height="16" role="img" version="1.1" viewBox="0 0 16 16" width="16"><path d="M8.06 2C3 2 0 8 0 8s3 6 8.06 6c4.94 0 7.94-6 7.94-6S13 2 8.06 2z m-0.06 10c-2.2 0-4-1.78-4-4 0-2.2 1.8-4 4-4 2.22 0 4 1.8 4 4 0 2.22-1.78 4-4 4z m2-4c0 1.11-0.89 2-2 2s-2-0.89-2-2 0.89-2 2-2 2 0.89 2 2z"></path></svg>
    Watch
  </a>
  <a class="social-count" href="/ModernMT/mosesdecoder/watchers">
    9
  </a>

  </li>

  <li>
      <a href="/login?return_to=%2FModernMT%2Fmosesdecoder"
    class="btn btn-sm btn-with-count tooltipped tooltipped-n"
    aria-label="You must be signed in to star a repository" rel="nofollow">
    <svg aria-hidden="true" class="octicon octicon-star" height="16" role="img" version="1.1" viewBox="0 0 14 16" width="14"><path d="M14 6l-4.9-0.64L7 1 4.9 5.36 0 6l3.6 3.26L2.67 14l4.33-2.33 4.33 2.33L10.4 9.26 14 6z"></path></svg>
    Star
  </a>

    <a class="social-count js-social-count" href="/ModernMT/mosesdecoder/stargazers">
      1
    </a>

  </li>

  <li>
      <a href="/login?return_to=%2FModernMT%2Fmosesdecoder"
        class="btn btn-sm btn-with-count tooltipped tooltipped-n"
        aria-label="You must be signed in to fork a repository" rel="nofollow">
        <svg aria-hidden="true" class="octicon octicon-repo-forked" height="16" role="img" version="1.1" viewBox="0 0 10 16" width="10"><path d="M8 1c-1.11 0-2 0.89-2 2 0 0.73 0.41 1.38 1 1.72v1.28L5 8 3 6v-1.28c0.59-0.34 1-0.98 1-1.72 0-1.11-0.89-2-2-2S0 1.89 0 3c0 0.73 0.41 1.38 1 1.72v1.78l3 3v1.78c-0.59 0.34-1 0.98-1 1.72 0 1.11 0.89 2 2 2s2-0.89 2-2c0-0.73-0.41-1.38-1-1.72V9.5l3-3V4.72c0.59-0.34 1-0.98 1-1.72 0-1.11-0.89-2-2-2zM2 4.2c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z m3 10c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z m3-10c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z"></path></svg>
        Fork
      </a>

    <a href="/ModernMT/mosesdecoder/network" class="social-count">
      271
    </a>
  </li>
</ul>

    <h1 class="entry-title public ">
  <svg aria-hidden="true" class="octicon octicon-repo-forked" height="16" role="img" version="1.1" viewBox="0 0 10 16" width="10"><path d="M8 1c-1.11 0-2 0.89-2 2 0 0.73 0.41 1.38 1 1.72v1.28L5 8 3 6v-1.28c0.59-0.34 1-0.98 1-1.72 0-1.11-0.89-2-2-2S0 1.89 0 3c0 0.73 0.41 1.38 1 1.72v1.78l3 3v1.78c-0.59 0.34-1 0.98-1 1.72 0 1.11 0.89 2 2 2s2-0.89 2-2c0-0.73-0.41-1.38-1-1.72V9.5l3-3V4.72c0.59-0.34 1-0.98 1-1.72 0-1.11-0.89-2-2-2zM2 4.2c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z m3 10c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z m3-10c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z"></path></svg>
  <span class="author" itemprop="author"><a href="/ModernMT" class="url fn" rel="author">ModernMT</a></span><!--
--><span class="path-divider">/</span><!--
--><strong itemprop="name"><a href="/ModernMT/mosesdecoder" data-pjax="#js-repo-pjax-container">mosesdecoder</a></strong>

  <span class="page-context-loader">
    <img alt="" height="16" src="https://assets-cdn.github.com/images/spinners/octocat-spinner-32.gif" width="16" />
  </span>

    <span class="fork-flag">
      <span class="text">forked from <a href="/moses-smt/mosesdecoder">moses-smt/mosesdecoder</a></span>
    </span>
</h1>

  </div>
  <div class="container">
    
<nav class="reponav js-repo-nav js-sidenav-container-pjax js-octicon-loaders"
     itemscope
     itemtype="http://schema.org/BreadcrumbList"
     role="navigation"
     data-pjax="#js-repo-pjax-container">

  <span itemscope itemtype="http://schema.org/ListItem" itemprop="itemListElement">
    <a href="/ModernMT/mosesdecoder/tree/mmt-dev" aria-selected="true" class="js-selected-navigation-item selected reponav-item" data-hotkey="g c" data-selected-links="repo_source repo_downloads repo_commits repo_releases repo_tags repo_branches /ModernMT/mosesdecoder/tree/mmt-dev" itemprop="url">
      <svg aria-hidden="true" class="octicon octicon-code" height="16" role="img" version="1.1" viewBox="0 0 14 16" width="14"><path d="M9.5 3l-1.5 1.5 3.5 3.5L8 11.5l1.5 1.5 4.5-5L9.5 3zM4.5 3L0 8l4.5 5 1.5-1.5L2.5 8l3.5-3.5L4.5 3z"></path></svg>
      <span itemprop="name">Code</span>
      <meta itemprop="position" content="1">
</a>  </span>


  <span itemscope itemtype="http://schema.org/ListItem" itemprop="itemListElement">
    <a href="/ModernMT/mosesdecoder/pulls" class="js-selected-navigation-item reponav-item" data-hotkey="g p" data-selected-links="repo_pulls /ModernMT/mosesdecoder/pulls" itemprop="url">
      <svg aria-hidden="true" class="octicon octicon-git-pull-request" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M11 11.28c0-1.73 0-6.28 0-6.28-0.03-0.78-0.34-1.47-0.94-2.06s-1.28-0.91-2.06-0.94c0 0-1.02 0-1 0V0L4 3l3 3V4h1c0.27 0.02 0.48 0.11 0.69 0.31s0.3 0.42 0.31 0.69v6.28c-0.59 0.34-1 0.98-1 1.72 0 1.11 0.89 2 2 2s2-0.89 2-2c0-0.73-0.41-1.38-1-1.72z m-1 2.92c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2zM4 3c0-1.11-0.89-2-2-2S0 1.89 0 3c0 0.73 0.41 1.38 1 1.72 0 1.55 0 5.56 0 6.56-0.59 0.34-1 0.98-1 1.72 0 1.11 0.89 2 2 2s2-0.89 2-2c0-0.73-0.41-1.38-1-1.72V4.72c0.59-0.34 1-0.98 1-1.72z m-0.8 10c0 0.66-0.55 1.2-1.2 1.2s-1.2-0.55-1.2-1.2 0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2z m-1.2-8.8c-0.66 0-1.2-0.55-1.2-1.2s0.55-1.2 1.2-1.2 1.2 0.55 1.2 1.2-0.55 1.2-1.2 1.2z"></path></svg>
      <span itemprop="name">Pull requests</span>
      <span class="counter">0</span>
      <meta itemprop="position" content="3">
</a>  </span>


  <a href="/ModernMT/mosesdecoder/pulse" class="js-selected-navigation-item reponav-item" data-selected-links="pulse /ModernMT/mosesdecoder/pulse">
    <svg aria-hidden="true" class="octicon octicon-pulse" height="16" role="img" version="1.1" viewBox="0 0 14 16" width="14"><path d="M11.5 8L8.8 5.4 6.6 8.5 5.5 1.6 2.38 8H0V10h3.6L4.5 8.2l0.9 5.4L9 8.5l1.6 1.5H14V8H11.5z"></path></svg>
    Pulse
</a>
  <a href="/ModernMT/mosesdecoder/graphs" class="js-selected-navigation-item reponav-item" data-selected-links="repo_graphs repo_contributors /ModernMT/mosesdecoder/graphs">
    <svg aria-hidden="true" class="octicon octicon-graph" height="16" role="img" version="1.1" viewBox="0 0 16 16" width="16"><path d="M16 14v1H0V0h1v14h15z m-11-1H3V8h2v5z m4 0H7V3h2v10z m4 0H11V6h2v7z"></path></svg>
    Graphs
</a>

</nav>

  </div>
</div>

<div class="container new-discussion-timeline experiment-repo-nav">
  <div class="repository-content">

    

<a href="/ModernMT/mosesdecoder/blob/750866128359131bad651b325826735b2da9f309/moses/TranslationModel/UG/mm/ug_bitext_sampler.h" class="hidden js-permalink-shortcut" data-hotkey="y">Permalink</a>

<!-- blob contrib key: blob_contributors:v21:4d77c8132ce8af44cc11516b3588cf6f -->

<div class="file-navigation js-zeroclipboard-container">
  
<div class="select-menu js-menu-container js-select-menu left">
  <button class="btn btn-sm select-menu-button js-menu-target css-truncate" data-hotkey="w"
    title="mmt-dev"
    type="button" aria-label="Switch branches or tags" tabindex="0" aria-haspopup="true">
    <i>Branch:</i>
    <span class="js-select-button css-truncate-target">mmt-dev</span>
  </button>

  <div class="select-menu-modal-holder js-menu-content js-navigation-container" data-pjax aria-hidden="true">

    <div class="select-menu-modal">
      <div class="select-menu-header">
        <svg aria-label="Close" class="octicon octicon-x js-menu-close" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M7.48 8l3.75 3.75-1.48 1.48-3.75-3.75-3.75 3.75-1.48-1.48 3.75-3.75L0.77 4.25l1.48-1.48 3.75 3.75 3.75-3.75 1.48 1.48-3.75 3.75z"></path></svg>
        <span class="select-menu-title">Switch branches/tags</span>
      </div>

      <div class="select-menu-filters">
        <div class="select-menu-text-filter">
          <input type="text" aria-label="Filter branches/tags" id="context-commitish-filter-field" class="js-filterable-field js-navigation-enable" placeholder="Filter branches/tags">
        </div>
        <div class="select-menu-tabs">
          <ul>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="branches" data-filter-placeholder="Filter branches/tags" class="js-select-menu-tab" role="tab">Branches</a>
            </li>
            <li class="select-menu-tab">
              <a href="#" data-tab-filter="tags" data-filter-placeholder="Find a tag…" class="js-select-menu-tab" role="tab">Tags</a>
            </li>
          </ul>
        </div>
      </div>

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="branches" role="menu">

        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/BEFORE_FF_FRAMEWORK/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="BEFORE_FF_FRAMEWORK"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="BEFORE_FF_FRAMEWORK">
                BEFORE_FF_FRAMEWORK
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/CheckTargetNgrams/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="CheckTargetNgrams"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="CheckTargetNgrams">
                CheckTargetNgrams
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/CompactPT/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="CompactPT"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="CompactPT">
                CompactPT
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/DPR_MOSES/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="DPR_MOSES"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="DPR_MOSES">
                DPR_MOSES
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/GHK/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="GHK"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="GHK">
                GHK
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/GHKMStruct/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="GHKMStruct"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="GHKMStruct">
                GHKMStruct
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/IRST_context_limit/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="IRST_context_limit"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="IRST_context_limit">
                IRST_context_limit
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/IRSTLM_threadsafe/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="IRSTLM_threadsafe"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="IRSTLM_threadsafe">
                IRSTLM_threadsafe
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ModernMT_adaptiveLM/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ModernMT_adaptiveLM"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ModernMT_adaptiveLM">
                ModernMT_adaptiveLM
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ModernMT_cdLM_backup/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ModernMT_cdLM_backup"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ModernMT_cdLM_backup">
                ModernMT_cdLM_backup
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ModernMT_cdLM/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ModernMT_cdLM"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ModernMT_cdLM">
                ModernMT_cdLM
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/RELEASE-0.91/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="RELEASE-0.91"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="RELEASE-0.91">
                RELEASE-0.91
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/RELEASE-1.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="RELEASE-1.0"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="RELEASE-1.0">
                RELEASE-1.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/RELEASE-2.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="RELEASE-2.1"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="RELEASE-2.1">
                RELEASE-2.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/RELEASE-2.1.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="RELEASE-2.1.1"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="RELEASE-2.1.1">
                RELEASE-2.1.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/RELEASE-3.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="RELEASE-3.0"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="RELEASE-3.0">
                RELEASE-3.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/abhi_discr/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="abhi_discr"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="abhi_discr">
                abhi_discr
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/amittai/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="amittai"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="amittai">
                amittai
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/andre_lynum/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="andre_lynum"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="andre_lynum">
                andre_lynum
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/android-ui/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="android-ui"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="android-ui">
                android-ui
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/apply-coding-standard/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="apply-coding-standard"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="apply-coding-standard">
                apply-coding-standard
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/async-factors/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="async-factors"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="async-factors">
                async-factors
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/augmLMResult/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="augmLMResult"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="augmLMResult">
                augmLMResult
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/auli_constraint/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="auli_constraint"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="auli_constraint">
                auli_constraint
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/bertoldi_onlinecommand/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="bertoldi_onlinecommand"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="bertoldi_onlinecommand">
                bertoldi_onlinecommand
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/biased-bitext-sampling/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="biased-bitext-sampling"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="biased-bitext-sampling">
                biased-bitext-sampling
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/bilingual-lm-paul/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="bilingual-lm-paul"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="bilingual-lm-paul">
                bilingual-lm-paul
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/bilingual-lm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="bilingual-lm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="bilingual-lm">
                bilingual-lm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/braune_longdist/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="braune_longdist"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="braune_longdist">
                braune_longdist
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/cdyer-multifactor/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="cdyer-multifactor"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="cdyer-multifactor">
                cdyer-multifactor
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/chardmeier-coref/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="chardmeier-coref"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="chardmeier-coref">
                chardmeier-coref
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/chardmeier-ldc/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="chardmeier-ldc"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="chardmeier-ldc">
                chardmeier-ldc
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/chardmeier-lminterp/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="chardmeier-lminterp"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="chardmeier-lminterp">
                chardmeier-lminterp
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/chart_alignments/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="chart_alignments"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="chart_alignments">
                chart_alignments
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/conditional-oxlm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="conditional-oxlm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="conditional-oxlm">
                conditional-oxlm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/config-switching/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="config-switching"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="config-switching">
                config-switching
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/damt-phrase2master/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="damt-phrase2master"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="damt-phrase2master">
                damt-phrase2master
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/damt_common/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="damt_common"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="damt_common">
                damt_common
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/damt_hiero/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="damt_hiero"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="damt_hiero">
                damt_hiero
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/damt_phrase/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="damt_phrase"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="damt_phrase">
                damt_phrase
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/david-cleanup-tsa/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="david-cleanup-tsa"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="david-cleanup-tsa">
                david-cleanup-tsa
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/david-merge/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="david-merge"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="david-merge">
                david-merge
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/david-profile-mmsapt/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="david-profile-mmsapt"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="david-profile-mmsapt">
                david-profile-mmsapt
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/debug-ranked3/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="debug-ranked3"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="debug-ranked3">
                debug-ranked3
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/dumb_psd/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="dumb_psd"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="dumb_psd">
                dumb_psd
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/dynamic-models/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="dynamic-models"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="dynamic-models">
                dynamic-models
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/dynamic-phrase-tables/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="dynamic-phrase-tables"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="dynamic-phrase-tables">
                dynamic-phrase-tables
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/dynsapt/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="dynsapt"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="dynsapt">
                dynsapt
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/eva_cube_pruning/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="eva_cube_pruning"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="eva_cube_pruning">
                eva_cube_pruning
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/eva_maxent/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="eva_maxent"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="eva_maxent">
                eva_maxent
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/factored_hacks/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="factored_hacks"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="factored_hacks">
                factored_hacks
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/fethi/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="fethi"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="fethi">
                fethi
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/fix-wchar-subscripts/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="fix-wchar-subscripts"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="fix-wchar-subscripts">
                fix-wchar-subscripts
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/fscorer/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="fscorer"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="fscorer">
                fscorer
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/get_top_weight/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="get_top_weight"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="get_top_weight">
                get_top_weight
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/grace_cube_pruning_gen/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="grace_cube_pruning_gen"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="grace_cube_pruning_gen">
                grace_cube_pruning_gen
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hierarchical-reo/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hierarchical-reo"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hierarchical-reo">
                hierarchical-reo
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu-async/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu-async"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu-async">
                hieu-async
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu_async/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu_async"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu_async">
                hieu_async
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu_combine/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu_combine"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu_combine">
                hieu_combine
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu_ftemplate/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu_ftemplate"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu_ftemplate">
                hieu_ftemplate
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu_ftemplate_2/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu_ftemplate_2"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu_ftemplate_2">
                hieu_ftemplate_2
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu_iphone/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu_iphone"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu_iphone">
                hieu_iphone
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu.oxlm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu.oxlm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu.oxlm">
                hieu.oxlm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/hieu/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="hieu"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="hieu">
                hieu
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/irstlm-adaptive-speed/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="irstlm-adaptive-speed"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="irstlm-adaptive-speed">
                irstlm-adaptive-speed
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/jjmoses/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="jjmoses"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="jjmoses">
                jjmoses
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/jointlm_improvements/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="jointlm_improvements"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="jointlm_improvements">
                jointlm_improvements
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/josiah/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="josiah"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="josiah">
                josiah
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/lane-constraint/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="lane-constraint"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="lane-constraint">
                lane-constraint
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/lane-mtm3/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="lane-mtm3"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="lane-mtm3">
                lane-mtm3
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/lane-multi/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="lane-multi"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="lane-multi">
                lane-multi
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/lane-syntax/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="lane-syntax"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="lane-syntax">
                lane-syntax
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/lexi-smoothing/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="lexi-smoothing"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="lexi-smoothing">
                lexi-smoothing
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/lexi_RELEASE-1.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="lexi_RELEASE-1.0"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="lexi_RELEASE-1.0">
                lexi_RELEASE-1.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/local_lms/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="local_lms"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="local_lms">
                local_lms
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/maria_HeadDrivenFeature/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="maria_HeadDrivenFeature"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="maria_HeadDrivenFeature">
                maria_HeadDrivenFeature
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/maria_MTM14/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="maria_MTM14"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="maria_MTM14">
                maria_MTM14
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/maria_SyntaxFeatures/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="maria_SyntaxFeatures"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="maria_SyntaxFeatures">
                maria_SyntaxFeatures
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/master/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="master"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="master">
                master
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/matecat_async/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="matecat_async"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="matecat_async">
                matecat_async
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mbotTestedDecoder/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mbotTestedDecoder"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mbotTestedDecoder">
                mbotTestedDecoder
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mbotdecoder/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mbotdecoder"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mbotdecoder">
                mbotdecoder
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/merge-cmd/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="merge-cmd"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="merge-cmd">
                merge-cmd
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mert-mtm5/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mert-mtm5"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mert-mtm5">
                mert-mtm5
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mert-other_metrics/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mert-other_metrics"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mert-other_metrics">
                mert-other_metrics
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mert-otherMetrics/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mert-otherMetrics"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mert-otherMetrics">
                mert-otherMetrics
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mingw-release-2.1.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mingw-release-2.1.1"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mingw-release-2.1.1">
                mingw-release-2.1.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/minphr/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="minphr"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="minphr">
                minphr
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mira-mtm5/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mira-mtm5"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mira-mtm5">
                mira-mtm5
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/miramerge/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="miramerge"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="miramerge">
                miramerge
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mmt-dev_issue49/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mmt-dev_issue49"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mmt-dev_issue49">
                mmt-dev_issue49
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open selected"
               href="/ModernMT/mosesdecoder/blob/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mmt-dev"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mmt-dev">
                mmt-dev
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mmt-merge/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mmt-merge"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mmt-merge">
                mmt-merge
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mmt-mmsapt-permacache/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mmt-mmsapt-permacache"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mmt-mmsapt-permacache">
                mmt-mmsapt-permacache
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/moses-batchedlm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="moses-batchedlm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="moses-batchedlm">
                moses-batchedlm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/moses-server/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="moses-server"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="moses-server">
                moses-server
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/moses+batchedlm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="moses+batchedlm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="moses+batchedlm">
                moses+batchedlm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/moses_cachebased/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="moses_cachebased"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="moses_cachebased">
                moses_cachebased
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mt3_chart/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mt3_chart"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mt3_chart">
                mt3_chart
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mt3_constraint/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mt3_constraint"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mt3_constraint">
                mt3_constraint
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mtm_lm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mtm_lm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mtm_lm">
                mtm_lm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mtm6-parallel-mert/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mtm6-parallel-mert"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mtm6-parallel-mert">
                mtm6-parallel-mert
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mtm6_cruise_control/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mtm6_cruise_control"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mtm6_cruise_control">
                mtm6_cruise_control
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mtm13_multipass_hieu/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mtm13_multipass_hieu"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mtm13_multipass_hieu">
                mtm13_multipass_hieu
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/mtm13_multipass/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="mtm13_multipass"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="mtm13_multipass">
                mtm13_multipass
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/multiple-models/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="multiple-models"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="multiple-models">
                multiple-models
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/multiple-models%403284/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="multiple-models@3284"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="multiple-models@3284">
                multiple-models@3284
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ni_DPR_reordering_model/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ni_DPR_reordering_model"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ni_DPR_reordering_model">
                ni_DPR_reordering_model
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ni_DPR_reordering_model2/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ni_DPR_reordering_model2"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ni_DPR_reordering_model2">
                ni_DPR_reordering_model2
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/norestart/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="norestart"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="norestart">
                norestart
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/nplm/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="nplm"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="nplm">
                nplm
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/old-ranked3-fixup-no2x/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="old-ranked3-fixup-no2x"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="old-ranked3-fixup-no2x">
                old-ranked3-fixup-no2x
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/old-ranked3-fixup/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="old-ranked3-fixup"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="old-ranked3-fixup">
                old-ranked3-fixup
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/oovpt/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="oovpt"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="oovpt">
                oovpt
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/prefix-private-cderscorer-member/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="prefix-private-cderscorer-member"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="prefix-private-cderscorer-member">
                prefix-private-cderscorer-member
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ranked-sampling/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ranked-sampling"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ranked-sampling">
                ranked-sampling
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/sa-domain-indexes/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="sa-domain-indexes"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="sa-domain-indexes">
                sa-domain-indexes
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/sa-index-unpacked/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="sa-index-unpacked"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="sa-index-unpacked">
                sa-index-unpacked
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/sa-ranked3/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="sa-ranked3"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="sa-ranked3">
                sa-ranked3
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/samplerank/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="samplerank"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="samplerank">
                samplerank
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/sapt-read-legacy-v1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="sapt-read-legacy-v1"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="sapt-read-legacy-v1">
                sapt-read-legacy-v1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/span-length/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="span-length"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="span-length">
                span-length
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/sparse-reordering/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="sparse-reordering"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="sparse-reordering">
                sparse-reordering
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/suffix_array/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="suffix_array"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="suffix_array">
                suffix_array
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/syntaxContext/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="syntaxContext"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="syntaxContext">
                syntaxContext
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/test-ranked3/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="test-ranked3"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="test-ranked3">
                test-ranked3
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/test2-ranked3/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="test2-ranked3"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="test2-ranked3">
                test2-ranked3
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/ug-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="ug-dev"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="ug-dev">
                ug-dev
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/vw_integration/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="vw_integration"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="vw_integration">
                vw_integration
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/wipo/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="wipo"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="wipo">
                wipo
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/wipoNew/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="wipoNew"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="wipoNew">
                wipoNew
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/wipoNewMerger/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="wipoNewMerger"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="wipoNewMerger">
                wipoNewMerger
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/yanggao-softdep-hiero/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="yanggao-softdep-hiero"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="yanggao-softdep-hiero">
                yanggao-softdep-hiero
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
               href="/ModernMT/mosesdecoder/blob/yanggao_maxent/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
               data-name="yanggao_maxent"
               data-skip-pjax="true"
               rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target js-select-menu-filter-text" title="yanggao_maxent">
                yanggao_maxent
              </span>
            </a>
        </div>

          <div class="select-menu-no-results">Nothing to show</div>
      </div>

      <div class="select-menu-list select-menu-tab-bucket js-select-menu-tab-bucket" data-tab-filter="tags">
        <div data-filterable-for="context-commitish-filter-field" data-filterable-type="substring">


            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/ranked-sampling-v0.1.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="ranked-sampling-v0.1.0"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="ranked-sampling-v0.1.0">
                ranked-sampling-v0.1.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/pre-MMT/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="pre-MMT"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="pre-MMT">
                pre-MMT
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mtm_before_cube_pruning/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mtm_before_cube_pruning"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mtm_before_cube_pruning">
                mtm_before_cube_pruning
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-ranked-sampling-v0.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-ranked-sampling-v0.1"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-ranked-sampling-v0.1">
                mmt-ranked-sampling-v0.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-mvp-v0.12.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-mvp-v0.12.1"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-mvp-v0.12.1">
                mmt-mvp-v0.12.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-mvp-v0.12.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-mvp-v0.12.0"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-mvp-v0.12.0">
                mmt-mvp-v0.12.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-mvp-v0.9.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-mvp-v0.9.0"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-mvp-v0.9.0">
                mmt-mvp-v0.9.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-mvp-v0.2.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-mvp-v0.2.1"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-mvp-v0.2.1">
                mmt-mvp-v0.2.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-mvp-0.2.0/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-mvp-0.2.0"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-mvp-0.2.0">
                mmt-mvp-0.2.0
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-dev_cdlm_v0.0.2/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-dev_cdlm_v0.0.2"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-dev_cdlm_v0.0.2">
                mmt-dev_cdlm_v0.0.2
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mmt-dev_cdlm_v0.0.1/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mmt-dev_cdlm_v0.0.1"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mmt-dev_cdlm_v0.0.1">
                mmt-dev_cdlm_v0.0.1
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/mira-mtm5_on-the-fly_paramater_updates_working/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="mira-mtm5_on-the-fly_paramater_updates_working"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="mira-mtm5_on-the-fly_paramater_updates_working">
                mira-mtm5_on-the-fly_paramater_updates_working
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/eva_2d_pruning%401521/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="eva_2d_pruning@1521"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="eva_2d_pruning@1521">
                eva_2d_pruning@1521
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/eva_2d_pruning%401488/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="eva_2d_pruning@1488"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="eva_2d_pruning@1488">
                eva_2d_pruning@1488
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/eva_2d_pruning/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="eva_2d_pruning"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="eva_2d_pruning">
                eva_2d_pruning
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/START_JHU/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="START_JHU"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="START_JHU">
                START_JHU
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/SCRIPTS-RELEASE-20060802-1746/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="SCRIPTS-RELEASE-20060802-1746"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="SCRIPTS-RELEASE-20060802-1746">
                SCRIPTS-RELEASE-20060802-1746
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/SCRIPTS-RELEASE-20060801-1856/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="SCRIPTS-RELEASE-20060801-1856"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="SCRIPTS-RELEASE-20060801-1856">
                SCRIPTS-RELEASE-20060801-1856
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/SCRIPTS-RELEASE-20060731-2118/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="SCRIPTS-RELEASE-20060731-2118"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="SCRIPTS-RELEASE-20060731-2118">
                SCRIPTS-RELEASE-20060731-2118
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/SCRIPTS-RELEASE-20060731-1701/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="SCRIPTS-RELEASE-20060731-1701"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="SCRIPTS-RELEASE-20060731-1701">
                SCRIPTS-RELEASE-20060731-1701
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/Root_HIEUS_BRANCH_2006_08_15/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="Root_HIEUS_BRANCH_2006_08_15"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="Root_HIEUS_BRANCH_2006_08_15">
                Root_HIEUS_BRANCH_2006_08_15
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/RELEASE-2006-07-26/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="RELEASE-2006-07-26"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="RELEASE-2006-07-26">
                RELEASE-2006-07-26
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/RELEASE-2006-07-14/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="RELEASE-2006-07-14"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="RELEASE-2006-07-14">
                RELEASE-2006-07-14
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/ModernMT_cdLM_v0.1alpha/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="ModernMT_cdLM_v0.1alpha"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="ModernMT_cdLM_v0.1alpha">
                ModernMT_cdLM_v0.1alpha
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/LAST-SINGLE-MODEL-ONLY-2010-08-09/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="LAST-SINGLE-MODEL-ONLY-2010-08-09"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="LAST-SINGLE-MODEL-ONLY-2010-08-09">
                LAST-SINGLE-MODEL-ONLY-2010-08-09
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/LAST-PHRASE-BASED-ONLY-2010-04-08/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="LAST-PHRASE-BASED-ONLY-2010-04-08"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="LAST-PHRASE-BASED-ONLY-2010-04-08">
                LAST-PHRASE-BASED-ONLY-2010-04-08
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/HIEU_THESIS/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="HIEU_THESIS"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="HIEU_THESIS">
                HIEU_THESIS
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/BEFORE_MERGE_MAIN/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="BEFORE_MERGE_MAIN"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="BEFORE_MERGE_MAIN">
                BEFORE_MERGE_MAIN
              </span>
            </a>
            <a class="select-menu-item js-navigation-item js-navigation-open "
              href="/ModernMT/mosesdecoder/tree/ABHISHEK_THESIS/moses/TranslationModel/UG/mm/ug_bitext_sampler.h"
              data-name="ABHISHEK_THESIS"
              data-skip-pjax="true"
              rel="nofollow">
              <svg aria-hidden="true" class="octicon octicon-check select-menu-item-icon" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M12 5L4 13 0 9l1.5-1.5 2.5 2.5 6.5-6.5 1.5 1.5z"></path></svg>
              <span class="select-menu-item-text css-truncate-target" title="ABHISHEK_THESIS">
                ABHISHEK_THESIS
              </span>
            </a>
        </div>

        <div class="select-menu-no-results">Nothing to show</div>
      </div>

    </div>
  </div>
</div>

  <div class="btn-group right">
    <a href="/ModernMT/mosesdecoder/find/mmt-dev"
          class="js-show-file-finder btn btn-sm"
          data-pjax
          data-hotkey="t">
      Find file
    </a>
    <button aria-label="Copy file path to clipboard" class="js-zeroclipboard btn btn-sm zeroclipboard-button tooltipped tooltipped-s" data-copied-hint="Copied!" type="button">Copy path</button>
  </div>
  <div class="breadcrumb js-zeroclipboard-target">
    <span class="repo-root js-repo-root"><span class="js-path-segment"><a href="/ModernMT/mosesdecoder/tree/mmt-dev"><span>mosesdecoder</span></a></span></span><span class="separator">/</span><span class="js-path-segment"><a href="/ModernMT/mosesdecoder/tree/mmt-dev/moses"><span>moses</span></a></span><span class="separator">/</span><span class="js-path-segment"><a href="/ModernMT/mosesdecoder/tree/mmt-dev/moses/TranslationModel"><span>TranslationModel</span></a></span><span class="separator">/</span><span class="js-path-segment"><a href="/ModernMT/mosesdecoder/tree/mmt-dev/moses/TranslationModel/UG"><span>UG</span></a></span><span class="separator">/</span><span class="js-path-segment"><a href="/ModernMT/mosesdecoder/tree/mmt-dev/moses/TranslationModel/UG/mm"><span>mm</span></a></span><span class="separator">/</span><strong class="final-path">ug_bitext_sampler.h</strong>
  </div>
</div>


  <div class="commit-tease">
      <span class="right">
        <a class="commit-tease-sha" href="/ModernMT/mosesdecoder/commit/90d4bd14f1f46780e94b37f4e96a9ddc1ca30c70" data-pjax>
          90d4bd1
        </a>
        <time datetime="2016-03-09T17:05:34Z" is="relative-time">Mar 9, 2016</time>
      </span>
      <div>
        <img alt="@cidermole" class="avatar" height="20" src="https://avatars0.githubusercontent.com/u/847573?v=3&amp;s=40" width="20" />
        <a href="/cidermole" class="user-mention" rel="contributor">cidermole</a>
          <a href="/ModernMT/mosesdecoder/commit/90d4bd14f1f46780e94b37f4e96a9ddc1ca30c70" class="message" data-pjax="true" title="use uniform_collect() instead of ranked3_collect() for ranked sampling core">use uniform_collect() instead of ranked3_collect() for ranked samplin…</a>
      </div>

    <div class="commit-tease-contributors">
      <button type="button" class="btn-link muted-link contributors-toggle" data-facebox="#blob_contributors_box">
        <strong>3</strong>
         contributors
      </button>
          <a class="avatar-link tooltipped tooltipped-s" aria-label="ugermann" href="/ModernMT/mosesdecoder/commits/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h?author=ugermann"><img alt="@ugermann" class="avatar" height="20" src="https://avatars0.githubusercontent.com/u/4459323?v=3&amp;s=40" width="20" /> </a>
    <a class="avatar-link tooltipped tooltipped-s" aria-label="cidermole" href="/ModernMT/mosesdecoder/commits/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h?author=cidermole"><img alt="@cidermole" class="avatar" height="20" src="https://avatars0.githubusercontent.com/u/847573?v=3&amp;s=40" width="20" /> </a>
    <a class="avatar-link tooltipped tooltipped-s" aria-label="davidecaroselli" href="/ModernMT/mosesdecoder/commits/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h?author=davidecaroselli"><img alt="@davidecaroselli" class="avatar" height="20" src="https://avatars3.githubusercontent.com/u/1674891?v=3&amp;s=40" width="20" /> </a>


    </div>

    <div id="blob_contributors_box" style="display:none">
      <h2 class="facebox-header" data-facebox-id="facebox-header">Users who have contributed to this file</h2>
      <ul class="facebox-user-list" data-facebox-id="facebox-description">
          <li class="facebox-user-list-item">
            <img alt="@ugermann" height="24" src="https://avatars2.githubusercontent.com/u/4459323?v=3&amp;s=48" width="24" />
            <a href="/ugermann">ugermann</a>
          </li>
          <li class="facebox-user-list-item">
            <img alt="@cidermole" height="24" src="https://avatars2.githubusercontent.com/u/847573?v=3&amp;s=48" width="24" />
            <a href="/cidermole">cidermole</a>
          </li>
          <li class="facebox-user-list-item">
            <img alt="@davidecaroselli" height="24" src="https://avatars1.githubusercontent.com/u/1674891?v=3&amp;s=48" width="24" />
            <a href="/davidecaroselli">davidecaroselli</a>
          </li>
      </ul>
    </div>
  </div>

<div class="file">
  <div class="file-header">
  <div class="file-actions">

    <div class="btn-group">
      <a href="/ModernMT/mosesdecoder/raw/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h" class="btn btn-sm " id="raw-url">Raw</a>
        <a href="/ModernMT/mosesdecoder/blame/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h" class="btn btn-sm js-update-url-with-hash">Blame</a>
      <a href="/ModernMT/mosesdecoder/commits/mmt-dev/moses/TranslationModel/UG/mm/ug_bitext_sampler.h" class="btn btn-sm " rel="nofollow">History</a>
    </div>


        <button type="button" class="btn-octicon disabled tooltipped tooltipped-nw"
          aria-label="You must be signed in to make or propose changes">
          <svg aria-hidden="true" class="octicon octicon-pencil" height="16" role="img" version="1.1" viewBox="0 0 14 16" width="14"><path d="M0 12v3h3l8-8-3-3L0 12z m3 2H1V12h1v1h1v1z m10.3-9.3l-1.3 1.3-3-3 1.3-1.3c0.39-0.39 1.02-0.39 1.41 0l1.59 1.59c0.39 0.39 0.39 1.02 0 1.41z"></path></svg>
        </button>
        <button type="button" class="btn-octicon btn-octicon-danger disabled tooltipped tooltipped-nw"
          aria-label="You must be signed in to make or propose changes">
          <svg aria-hidden="true" class="octicon octicon-trashcan" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M10 2H8c0-0.55-0.45-1-1-1H4c-0.55 0-1 0.45-1 1H1c-0.55 0-1 0.45-1 1v1c0 0.55 0.45 1 1 1v9c0 0.55 0.45 1 1 1h7c0.55 0 1-0.45 1-1V5c0.55 0 1-0.45 1-1v-1c0-0.55-0.45-1-1-1z m-1 12H2V5h1v8h1V5h1v8h1V5h1v8h1V5h1v9z m1-10H1v-1h9v1z"></path></svg>
        </button>
  </div>

  <div class="file-info">
      144 lines (118 sloc)
      <span class="file-info-divider"></span>
    4.64 KB
  </div>
</div>

  

  <div itemprop="text" class="blob-wrapper data type-c">
      <table class="highlight tab-size js-file-line-container" data-tab-size="8">
      <tr>
        <td id="L1" class="blob-num js-line-number" data-line-number="1"></td>
        <td id="LC1" class="blob-code blob-code-inner js-file-line"><span class="pl-c">// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil -*-</span></td>
      </tr>
      <tr>
        <td id="L2" class="blob-num js-line-number" data-line-number="2"></td>
        <td id="LC2" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">pragma</span> once</td>
      </tr>
      <tr>
        <td id="L3" class="blob-num js-line-number" data-line-number="3"></td>
        <td id="LC3" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L4" class="blob-num js-line-number" data-line-number="4"></td>
        <td id="LC4" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>algorithm<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L5" class="blob-num js-line-number" data-line-number="5"></td>
        <td id="LC5" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L6" class="blob-num js-line-number" data-line-number="6"></td>
        <td id="LC6" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/random.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L7" class="blob-num js-line-number" data-line-number="7"></td>
        <td id="LC7" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/thread.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L8" class="blob-num js-line-number" data-line-number="8"></td>
        <td id="LC8" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/thread/locks.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L9" class="blob-num js-line-number" data-line-number="9"></td>
        <td id="LC9" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/intrusive_ptr.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L10" class="blob-num js-line-number" data-line-number="10"></td>
        <td id="LC10" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/unordered_set.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L11" class="blob-num js-line-number" data-line-number="11"></td>
        <td id="LC11" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&lt;</span>boost/math/distributions/binomial.hpp<span class="pl-pds">&gt;</span></span></td>
      </tr>
      <tr>
        <td id="L12" class="blob-num js-line-number" data-line-number="12"></td>
        <td id="LC12" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L13" class="blob-num js-line-number" data-line-number="13"></td>
        <td id="LC13" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>ug_bitext.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L14" class="blob-num js-line-number" data-line-number="14"></td>
        <td id="LC14" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>ug_bitext_pstats.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L15" class="blob-num js-line-number" data-line-number="15"></td>
        <td id="LC15" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>ug_sampling_bias.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L16" class="blob-num js-line-number" data-line-number="16"></td>
        <td id="LC16" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>ug_tsa_array_entry.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L17" class="blob-num js-line-number" data-line-number="17"></td>
        <td id="LC17" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>ug_bitext_phrase_extraction_record.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L18" class="blob-num js-line-number" data-line-number="18"></td>
        <td id="LC18" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>moses/TranslationModel/UG/generic/threading/ug_ref_counter.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L19" class="blob-num js-line-number" data-line-number="19"></td>
        <td id="LC19" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>moses/TranslationModel/UG/generic/threading/ug_thread_safe_counter.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L20" class="blob-num js-line-number" data-line-number="20"></td>
        <td id="LC20" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>moses/TranslationModel/UG/generic/sorting/NBestList.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L21" class="blob-num js-line-number" data-line-number="21"></td>
        <td id="LC21" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L22" class="blob-num js-line-number" data-line-number="22"></td>
        <td id="LC22" class="blob-code blob-code-inner js-file-line">#<span class="pl-k">include</span> <span class="pl-s"><span class="pl-pds">&quot;</span>fisheryates.h<span class="pl-pds">&quot;</span></span></td>
      </tr>
      <tr>
        <td id="L23" class="blob-num js-line-number" data-line-number="23"></td>
        <td id="LC23" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L24" class="blob-num js-line-number" data-line-number="24"></td>
        <td id="LC24" class="blob-code blob-code-inner js-file-line"><span class="pl-k">namespace</span> <span class="pl-en">sapt</span></td>
      </tr>
      <tr>
        <td id="L25" class="blob-num js-line-number" data-line-number="25"></td>
        <td id="LC25" class="blob-code blob-code-inner js-file-line">{</td>
      </tr>
      <tr>
        <td id="L26" class="blob-num js-line-number" data-line-number="26"></td>
        <td id="LC26" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L27" class="blob-num js-line-number" data-line-number="27"></td>
        <td id="LC27" class="blob-code blob-code-inner js-file-line"><span class="pl-k">typedef</span> std::vector&lt;id_type&gt; SrcPhrase;</td>
      </tr>
      <tr>
        <td id="L28" class="blob-num js-line-number" data-line-number="28"></td>
        <td id="LC28" class="blob-code blob-code-inner js-file-line"><span class="pl-k">typedef</span> std::<span class="pl-c1">size_t</span> <span class="pl-c1">size_t</span>;  <span class="pl-c">// make CLion happy</span></td>
      </tr>
      <tr>
        <td id="L29" class="blob-num js-line-number" data-line-number="29"></td>
        <td id="LC29" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L30" class="blob-num js-line-number" data-line-number="30"></td>
        <td id="LC30" class="blob-code blob-code-inner js-file-line"><span class="pl-k">enum</span> </td>
      </tr>
      <tr>
        <td id="L31" class="blob-num js-line-number" data-line-number="31"></td>
        <td id="LC31" class="blob-code blob-code-inner js-file-line">sampling_method </td>
      </tr>
      <tr>
        <td id="L32" class="blob-num js-line-number" data-line-number="32"></td>
        <td id="LC32" class="blob-code blob-code-inner js-file-line">  { </td>
      </tr>
      <tr>
        <td id="L33" class="blob-num js-line-number" data-line-number="33"></td>
        <td id="LC33" class="blob-code blob-code-inner js-file-line">    full_coverage, </td>
      </tr>
      <tr>
        <td id="L34" class="blob-num js-line-number" data-line-number="34"></td>
        <td id="LC34" class="blob-code blob-code-inner js-file-line">    random_sampling, </td>
      </tr>
      <tr>
        <td id="L35" class="blob-num js-line-number" data-line-number="35"></td>
        <td id="LC35" class="blob-code blob-code-inner js-file-line">    ranked_sampling, </td>
      </tr>
      <tr>
        <td id="L36" class="blob-num js-line-number" data-line-number="36"></td>
        <td id="LC36" class="blob-code blob-code-inner js-file-line">    ranked_sampling2,</td>
      </tr>
      <tr>
        <td id="L37" class="blob-num js-line-number" data-line-number="37"></td>
        <td id="LC37" class="blob-code blob-code-inner js-file-line">    ranked_sampling3</td>
      </tr>
      <tr>
        <td id="L38" class="blob-num js-line-number" data-line-number="38"></td>
        <td id="LC38" class="blob-code blob-code-inner js-file-line">  };</td>
      </tr>
      <tr>
        <td id="L39" class="blob-num js-line-number" data-line-number="39"></td>
        <td id="LC39" class="blob-code blob-code-inner js-file-line">  </td>
      </tr>
      <tr>
        <td id="L40" class="blob-num js-line-number" data-line-number="40"></td>
        <td id="LC40" class="blob-code blob-code-inner js-file-line"><span class="pl-k">typedef</span> ttrack::Position TokenPosition;</td>
      </tr>
      <tr>
        <td id="L41" class="blob-num js-line-number" data-line-number="41"></td>
        <td id="LC41" class="blob-code blob-code-inner js-file-line"><span class="pl-k">class</span> <span class="pl-en">CandidateSorter</span></td>
      </tr>
      <tr>
        <td id="L42" class="blob-num js-line-number" data-line-number="42"></td>
        <td id="LC42" class="blob-code blob-code-inner js-file-line">{</td>
      </tr>
      <tr>
        <td id="L43" class="blob-num js-line-number" data-line-number="43"></td>
        <td id="LC43" class="blob-code blob-code-inner js-file-line">  SamplingBias <span class="pl-k">const</span>&amp; score;</td>
      </tr>
      <tr>
        <td id="L44" class="blob-num js-line-number" data-line-number="44"></td>
        <td id="LC44" class="blob-code blob-code-inner js-file-line"><span class="pl-k">public:</span></td>
      </tr>
      <tr>
        <td id="L45" class="blob-num js-line-number" data-line-number="45"></td>
        <td id="LC45" class="blob-code blob-code-inner js-file-line">  <span class="pl-en">CandidateSorter</span>(SamplingBias <span class="pl-k">const</span>&amp; s) : score(s) {}</td>
      </tr>
      <tr>
        <td id="L46" class="blob-num js-line-number" data-line-number="46"></td>
        <td id="LC46" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span> <span class="pl-en">operator</span>()(TokenPosition <span class="pl-k">const</span>&amp; a, TokenPosition <span class="pl-k">const</span>&amp; b) <span class="pl-k">const</span></td>
      </tr>
      <tr>
        <td id="L47" class="blob-num js-line-number" data-line-number="47"></td>
        <td id="LC47" class="blob-code blob-code-inner js-file-line">  { <span class="pl-k">return</span> score[a.<span class="pl-smi">sid</span>] &gt; score[b.<span class="pl-smi">sid</span>]; }</td>
      </tr>
      <tr>
        <td id="L48" class="blob-num js-line-number" data-line-number="48"></td>
        <td id="LC48" class="blob-code blob-code-inner js-file-line">};</td>
      </tr>
      <tr>
        <td id="L49" class="blob-num js-line-number" data-line-number="49"></td>
        <td id="LC49" class="blob-code blob-code-inner js-file-line">  </td>
      </tr>
      <tr>
        <td id="L50" class="blob-num js-line-number" data-line-number="50"></td>
        <td id="LC50" class="blob-code blob-code-inner js-file-line"><span class="pl-k">template</span>&lt;<span class="pl-k">typename</span> Token&gt;</td>
      </tr>
      <tr>
        <td id="L51" class="blob-num js-line-number" data-line-number="51"></td>
        <td id="LC51" class="blob-code blob-code-inner js-file-line"><span class="pl-k">class</span></td>
      </tr>
      <tr>
        <td id="L52" class="blob-num js-line-number" data-line-number="52"></td>
        <td id="LC52" class="blob-code blob-code-inner js-file-line">BitextSampler : public Moses::reference_counter</td>
      </tr>
      <tr>
        <td id="L53" class="blob-num js-line-number" data-line-number="53"></td>
        <td id="LC53" class="blob-code blob-code-inner js-file-line">{</td>
      </tr>
      <tr>
        <td id="L54" class="blob-num js-line-number" data-line-number="54"></td>
        <td id="LC54" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">typedef</span> Bitext&lt;Token&gt; bitext;</td>
      </tr>
      <tr>
        <td id="L55" class="blob-num js-line-number" data-line-number="55"></td>
        <td id="LC55" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">typedef</span> TSA&lt;Token&gt;       tsa;</td>
      </tr>
      <tr>
        <td id="L56" class="blob-num js-line-number" data-line-number="56"></td>
        <td id="LC56" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">typedef</span> SamplingBias    <span class="pl-c1">bias_t</span>;</td>
      </tr>
      <tr>
        <td id="L57" class="blob-num js-line-number" data-line-number="57"></td>
        <td id="LC57" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">typedef</span> <span class="pl-k">typename</span> Bitext&lt;Token&gt;::iter tsa_iter;</td>
      </tr>
      <tr>
        <td id="L58" class="blob-num js-line-number" data-line-number="58"></td>
        <td id="LC58" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">mutable</span> boost::condition_variable   m_ready; </td>
      </tr>
      <tr>
        <td id="L59" class="blob-num js-line-number" data-line-number="59"></td>
        <td id="LC59" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">mutable</span> boost::mutex                 m_lock; </td>
      </tr>
      <tr>
        <td id="L60" class="blob-num js-line-number" data-line-number="60"></td>
        <td id="LC60" class="blob-code blob-code-inner js-file-line">  <span class="pl-c">// const members</span></td>
      </tr>
      <tr>
        <td id="L61" class="blob-num js-line-number" data-line-number="61"></td>
        <td id="LC61" class="blob-code blob-code-inner js-file-line">  <span class="pl-c">// SPTR&lt;bitext const&gt; const   m_bitext; // keep bitext alive while I am </span></td>
      </tr>
      <tr>
        <td id="L62" class="blob-num js-line-number" data-line-number="62"></td>
        <td id="LC62" class="blob-code blob-code-inner js-file-line">  <span class="pl-c">// should be an </span></td>
      </tr>
      <tr>
        <td id="L63" class="blob-num js-line-number" data-line-number="63"></td>
        <td id="LC63" class="blob-code blob-code-inner js-file-line">  SPTR&lt;bitext <span class="pl-k">const</span>&gt; <span class="pl-k">const</span>       m_bitext; <span class="pl-c">// keep bitext alive as long as I am </span></td>
      </tr>
      <tr>
        <td id="L64" class="blob-num js-line-number" data-line-number="64"></td>
        <td id="LC64" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span>             <span class="pl-k">const</span>         m_plen; <span class="pl-c">// length of lookup phrase</span></td>
      </tr>
      <tr>
        <td id="L65" class="blob-num js-line-number" data-line-number="65"></td>
        <td id="LC65" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span>               <span class="pl-k">const</span>          m_fwd; <span class="pl-c">// forward or backward direction?</span></td>
      </tr>
      <tr>
        <td id="L66" class="blob-num js-line-number" data-line-number="66"></td>
        <td id="LC66" class="blob-code blob-code-inner js-file-line">  SPTR&lt;tsa <span class="pl-k">const</span>&gt;    <span class="pl-k">const</span>         m_root; <span class="pl-c">// root of suffix array</span></td>
      </tr>
      <tr>
        <td id="L67" class="blob-num js-line-number" data-line-number="67"></td>
        <td id="LC67" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">char</span>               <span class="pl-k">const</span>*        m_next; <span class="pl-c">// current position</span></td>
      </tr>
      <tr>
        <td id="L68" class="blob-num js-line-number" data-line-number="68"></td>
        <td id="LC68" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">char</span>               <span class="pl-k">const</span>*        m_stop; <span class="pl-c">// end of search range</span></td>
      </tr>
      <tr>
        <td id="L69" class="blob-num js-line-number" data-line-number="69"></td>
        <td id="LC69" class="blob-code blob-code-inner js-file-line">  sampling_method    <span class="pl-k">const</span>       m_method; <span class="pl-c">// look at all/random/ranked samples </span></td>
      </tr>
      <tr>
        <td id="L70" class="blob-num js-line-number" data-line-number="70"></td>
        <td id="LC70" class="blob-code blob-code-inner js-file-line">  SPTR&lt;<span class="pl-c1">bias_t</span> <span class="pl-k">const</span>&gt; <span class="pl-k">const</span>         m_bias; <span class="pl-c">// bias over candidates</span></td>
      </tr>
      <tr>
        <td id="L71" class="blob-num js-line-number" data-line-number="71"></td>
        <td id="LC71" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span>             <span class="pl-k">const</span>      m_samples; <span class="pl-c">// how many samples at most </span></td>
      </tr>
      <tr>
        <td id="L72" class="blob-num js-line-number" data-line-number="72"></td>
        <td id="LC72" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span>             <span class="pl-k">const</span>  m_min_samples;</td>
      </tr>
      <tr>
        <td id="L73" class="blob-num js-line-number" data-line-number="73"></td>
        <td id="LC73" class="blob-code blob-code-inner js-file-line">  <span class="pl-c">// non-const members</span></td>
      </tr>
      <tr>
        <td id="L74" class="blob-num js-line-number" data-line-number="74"></td>
        <td id="LC74" class="blob-code blob-code-inner js-file-line">  SPTR&lt;pstats&gt;                m_stats; <span class="pl-c">// destination for phrase stats</span></td>
      </tr>
      <tr>
        <td id="L75" class="blob-num js-line-number" data-line-number="75"></td>
        <td id="LC75" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span>                        m_ctr; <span class="pl-c">// number of samples considered</span></td>
      </tr>
      <tr>
        <td id="L76" class="blob-num js-line-number" data-line-number="76"></td>
        <td id="LC76" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">float</span>                  m_total_bias; <span class="pl-c">// for random sampling with bias</span></td>
      </tr>
      <tr>
        <td id="L77" class="blob-num js-line-number" data-line-number="77"></td>
        <td id="LC77" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span>                     m_finished;</td>
      </tr>
      <tr>
        <td id="L78" class="blob-num js-line-number" data-line-number="78"></td>
        <td id="LC78" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> m_num_occurrences; <span class="pl-c">// estimated number of phrase occurrences in corpus</span></td>
      </tr>
      <tr>
        <td id="L79" class="blob-num js-line-number" data-line-number="79"></td>
        <td id="LC79" class="blob-code blob-code-inner js-file-line">  boost::taus88 m_rnd;  <span class="pl-c">// every job has its own pseudo random generator</span></td>
      </tr>
      <tr>
        <td id="L80" class="blob-num js-line-number" data-line-number="80"></td>
        <td id="LC80" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">double</span> m_bias_total;</td>
      </tr>
      <tr>
        <td id="L81" class="blob-num js-line-number" data-line-number="81"></td>
        <td id="LC81" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L82" class="blob-num js-line-number" data-line-number="82"></td>
        <td id="LC82" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-c1">m_random_size_t</span>;</td>
      </tr>
      <tr>
        <td id="L83" class="blob-num js-line-number" data-line-number="83"></td>
        <td id="LC83" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">double</span> m_rnd_float;</td>
      </tr>
      <tr>
        <td id="L84" class="blob-num js-line-number" data-line-number="84"></td>
        <td id="LC84" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L85" class="blob-num js-line-number" data-line-number="85"></td>
        <td id="LC85" class="blob-code blob-code-inner js-file-line">  SrcPhrase m_phrase;</td>
      </tr>
      <tr>
        <td id="L86" class="blob-num js-line-number" data-line-number="86"></td>
        <td id="LC86" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L87" class="blob-num js-line-number" data-line-number="87"></td>
        <td id="LC87" class="blob-code blob-code-inner js-file-line">  <span class="pl-c">/**</span></td>
      </tr>
      <tr>
        <td id="L88" class="blob-num js-line-number" data-line-number="88"></td>
        <td id="LC88" class="blob-code blob-code-inner js-file-line"><span class="pl-c">   * Attempt to extract a phrase pair, and on success, add it to m_stats.</span></td>
      </tr>
      <tr>
        <td id="L89" class="blob-num js-line-number" data-line-number="89"></td>
        <td id="LC89" class="blob-code blob-code-inner js-file-line"><span class="pl-c">   * @param p: the source phrase (as corpus location + implicit length in m_plen)</span></td>
      </tr>
      <tr>
        <td id="L90" class="blob-num js-line-number" data-line-number="90"></td>
        <td id="LC90" class="blob-code blob-code-inner js-file-line"><span class="pl-c">   * @ param i1: corpus index 1 to use (may be domain-specific)</span></td>
      </tr>
      <tr>
        <td id="L91" class="blob-num js-line-number" data-line-number="91"></td>
        <td id="LC91" class="blob-code blob-code-inner js-file-line"><span class="pl-c">   * @ param i2: index 2</span></td>
      </tr>
      <tr>
        <td id="L92" class="blob-num js-line-number" data-line-number="92"></td>
        <td id="LC92" class="blob-code blob-code-inner js-file-line"><span class="pl-c">   */</span></td>
      </tr>
      <tr>
        <td id="L93" class="blob-num js-line-number" data-line-number="93"></td>
        <td id="LC93" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">consider_sample</span>(TokenPosition <span class="pl-k">const</span>&amp; p, SPTR&lt;TSA&lt;Token&gt; &gt; i1, SPTR&lt;TSA&lt;Token&gt; &gt; i2);</td>
      </tr>
      <tr>
        <td id="L94" class="blob-num js-line-number" data-line-number="94"></td>
        <td id="LC94" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L95" class="blob-num js-line-number" data-line-number="95"></td>
        <td id="LC95" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">consider_sample</span>(TokenPosition <span class="pl-k">const</span>&amp; p);</td>
      </tr>
      <tr>
        <td id="L96" class="blob-num js-line-number" data-line-number="96"></td>
        <td id="LC96" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L97" class="blob-num js-line-number" data-line-number="97"></td>
        <td id="LC97" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">perform_ranked_sampling</span>();</td>
      </tr>
      <tr>
        <td id="L98" class="blob-num js-line-number" data-line-number="98"></td>
        <td id="LC98" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">perform_ranked_sampling2</span>();</td>
      </tr>
      <tr>
        <td id="L99" class="blob-num js-line-number" data-line-number="99"></td>
        <td id="LC99" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L100" class="blob-num js-line-number" data-line-number="100"></td>
        <td id="LC100" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">perform_ranked_sampling3</span>();</td>
      </tr>
      <tr>
        <td id="L101" class="blob-num js-line-number" data-line-number="101"></td>
        <td id="LC101" class="blob-code blob-code-inner js-file-line"><span class="pl-c">//  size_t ranked3_collect(size_t samples, SPTR&lt;TSA&lt;Token&gt; &gt; i1, SPTR&lt;TSA&lt;Token&gt; &gt; i2);</span></td>
      </tr>
      <tr>
        <td id="L102" class="blob-num js-line-number" data-line-number="102"></td>
        <td id="LC102" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">uniform_collect</span>(<span class="pl-c1">size_t</span> samples, <span class="pl-k">const</span> std::vector&lt;id_type&gt;&amp; domains);</td>
      </tr>
      <tr>
        <td id="L103" class="blob-num js-line-number" data-line-number="103"></td>
        <td id="LC103" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L104" class="blob-num js-line-number" data-line-number="104"></td>
        <td id="LC104" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L105" class="blob-num js-line-number" data-line-number="105"></td>
        <td id="LC105" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">perform_random_sampling</span>();</td>
      </tr>
      <tr>
        <td id="L106" class="blob-num js-line-number" data-line-number="106"></td>
        <td id="LC106" class="blob-code blob-code-inner js-file-line">  <span class="pl-c1">size_t</span> <span class="pl-en">perform_full_phrase_extraction</span>();</td>
      </tr>
      <tr>
        <td id="L107" class="blob-num js-line-number" data-line-number="107"></td>
        <td id="LC107" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L108" class="blob-num js-line-number" data-line-number="108"></td>
        <td id="LC108" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">int</span> <span class="pl-en">check_sample_distribution</span>(<span class="pl-c1">uint64_t</span> <span class="pl-k">const</span>&amp; sid, <span class="pl-c1">uint64_t</span> <span class="pl-k">const</span>&amp; offset);</td>
      </tr>
      <tr>
        <td id="L109" class="blob-num js-line-number" data-line-number="109"></td>
        <td id="LC109" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span> <span class="pl-en">flip_coin</span>(tpt::id_type <span class="pl-k">const</span>&amp; sid, tpt::offset_type <span class="pl-k">const</span>&amp; offset,</td>
      </tr>
      <tr>
        <td id="L110" class="blob-num js-line-number" data-line-number="110"></td>
        <td id="LC110" class="blob-code blob-code-inner js-file-line">                 SamplingBias <span class="pl-k">const</span>* bias);</td>
      </tr>
      <tr>
        <td id="L111" class="blob-num js-line-number" data-line-number="111"></td>
        <td id="LC111" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span> </td>
      </tr>
      <tr>
        <td id="L112" class="blob-num js-line-number" data-line-number="112"></td>
        <td id="LC112" class="blob-code blob-code-inner js-file-line">  <span class="pl-en">flip_coin</span>(<span class="pl-c1">size_t</span> options_total, </td>
      </tr>
      <tr>
        <td id="L113" class="blob-num js-line-number" data-line-number="113"></td>
        <td id="LC113" class="blob-code blob-code-inner js-file-line">            <span class="pl-c1">size_t</span> <span class="pl-k">const</span> options_considered, </td>
      </tr>
      <tr>
        <td id="L114" class="blob-num js-line-number" data-line-number="114"></td>
        <td id="LC114" class="blob-code blob-code-inner js-file-line">            <span class="pl-c1">size_t</span> <span class="pl-k">const</span> options_chosen,</td>
      </tr>
      <tr>
        <td id="L115" class="blob-num js-line-number" data-line-number="115"></td>
        <td id="LC115" class="blob-code blob-code-inner js-file-line">            <span class="pl-c1">size_t</span> <span class="pl-k">const</span> threshold);</td>
      </tr>
      <tr>
        <td id="L116" class="blob-num js-line-number" data-line-number="116"></td>
        <td id="LC116" class="blob-code blob-code-inner js-file-line">  </td>
      </tr>
      <tr>
        <td id="L117" class="blob-num js-line-number" data-line-number="117"></td>
        <td id="LC117" class="blob-code blob-code-inner js-file-line"><span class="pl-k">public:</span></td>
      </tr>
      <tr>
        <td id="L118" class="blob-num js-line-number" data-line-number="118"></td>
        <td id="LC118" class="blob-code blob-code-inner js-file-line">  <span class="pl-en">BitextSampler</span>(BitextSampler <span class="pl-k">const</span>&amp; other);</td>
      </tr>
      <tr>
        <td id="L119" class="blob-num js-line-number" data-line-number="119"></td>
        <td id="LC119" class="blob-code blob-code-inner js-file-line">  <span class="pl-c">// BitextSampler const&amp; operator=(BitextSampler const&amp; other);</span></td>
      </tr>
      <tr>
        <td id="L120" class="blob-num js-line-number" data-line-number="120"></td>
        <td id="LC120" class="blob-code blob-code-inner js-file-line">  <span class="pl-en">BitextSampler</span>(SPTR&lt;bitext <span class="pl-k">const</span>&gt; <span class="pl-k">const</span>&amp; bitext,</td>
      </tr>
      <tr>
        <td id="L121" class="blob-num js-line-number" data-line-number="121"></td>
        <td id="LC121" class="blob-code blob-code-inner js-file-line">                SrcPhrase <span class="pl-k">const</span>&amp; phrase,</td>
      </tr>
      <tr>
        <td id="L122" class="blob-num js-line-number" data-line-number="122"></td>
        <td id="LC122" class="blob-code blob-code-inner js-file-line">                <span class="pl-k">bool</span> fwd,</td>
      </tr>
      <tr>
        <td id="L123" class="blob-num js-line-number" data-line-number="123"></td>
        <td id="LC123" class="blob-code blob-code-inner js-file-line">                SPTR&lt;SamplingBias <span class="pl-k">const</span>&gt; <span class="pl-k">const</span>&amp; bias, </td>
      </tr>
      <tr>
        <td id="L124" class="blob-num js-line-number" data-line-number="124"></td>
        <td id="LC124" class="blob-code blob-code-inner js-file-line">                <span class="pl-c1">size_t</span> <span class="pl-k">const</span> min_samples, </td>
      </tr>
      <tr>
        <td id="L125" class="blob-num js-line-number" data-line-number="125"></td>
        <td id="LC125" class="blob-code blob-code-inner js-file-line">                <span class="pl-c1">size_t</span> <span class="pl-k">const</span> max_samples,</td>
      </tr>
      <tr>
        <td id="L126" class="blob-num js-line-number" data-line-number="126"></td>
        <td id="LC126" class="blob-code blob-code-inner js-file-line">                sampling_method <span class="pl-k">const</span> method); </td>
      </tr>
      <tr>
        <td id="L127" class="blob-num js-line-number" data-line-number="127"></td>
        <td id="LC127" class="blob-code blob-code-inner js-file-line">  <span class="pl-en">~BitextSampler</span>();</td>
      </tr>
      <tr>
        <td id="L128" class="blob-num js-line-number" data-line-number="128"></td>
        <td id="LC128" class="blob-code blob-code-inner js-file-line">  SPTR&lt;pstats&gt; <span class="pl-en">stats</span>();</td>
      </tr>
      <tr>
        <td id="L129" class="blob-num js-line-number" data-line-number="129"></td>
        <td id="LC129" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span> <span class="pl-en">done</span>() <span class="pl-k">const</span>;</td>
      </tr>
      <tr>
        <td id="L130" class="blob-num js-line-number" data-line-number="130"></td>
        <td id="LC130" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L131" class="blob-num js-line-number" data-line-number="131"></td>
        <td id="LC131" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span> <span class="pl-en">operator</span>()();</td>
      </tr>
      <tr>
        <td id="L132" class="blob-num js-line-number" data-line-number="132"></td>
        <td id="LC132" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L133" class="blob-num js-line-number" data-line-number="133"></td>
        <td id="LC133" class="blob-code blob-code-inner js-file-line"><span class="pl-c">// Ranked sampling sorts all samples by score and then considers the</span></td>
      </tr>
      <tr>
        <td id="L134" class="blob-num js-line-number" data-line-number="134"></td>
        <td id="LC134" class="blob-code blob-code-inner js-file-line"><span class="pl-c">// top-ranked candidates for phrase extraction.</span></td>
      </tr>
      <tr>
        <td id="L135" class="blob-num js-line-number" data-line-number="135"></td>
        <td id="LC135" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L136" class="blob-num js-line-number" data-line-number="136"></td>
        <td id="LC136" class="blob-code blob-code-inner js-file-line"><span class="pl-c">//namespace bitext {</span></td>
      </tr>
      <tr>
        <td id="L137" class="blob-num js-line-number" data-line-number="137"></td>
        <td id="LC137" class="blob-code blob-code-inner js-file-line"><span class="pl-k">private:</span></td>
      </tr>
      <tr>
        <td id="L138" class="blob-num js-line-number" data-line-number="138"></td>
        <td id="LC138" class="blob-code blob-code-inner js-file-line">  <span class="pl-k">bool</span> <span class="pl-en">is_good_sample</span>(TokenPosition <span class="pl-k">const</span>&amp; p);</td>
      </tr>
      <tr>
        <td id="L139" class="blob-num js-line-number" data-line-number="139"></td>
        <td id="LC139" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L140" class="blob-num js-line-number" data-line-number="140"></td>
        <td id="LC140" class="blob-code blob-code-inner js-file-line">};</td>
      </tr>
      <tr>
        <td id="L141" class="blob-num js-line-number" data-line-number="141"></td>
        <td id="LC141" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
      <tr>
        <td id="L142" class="blob-num js-line-number" data-line-number="142"></td>
        <td id="LC142" class="blob-code blob-code-inner js-file-line">} <span class="pl-c">// end of namespace sapt</span></td>
      </tr>
      <tr>
        <td id="L143" class="blob-num js-line-number" data-line-number="143"></td>
        <td id="LC143" class="blob-code blob-code-inner js-file-line">
</td>
      </tr>
</table>

  </div>

</div>

<button type="button" data-facebox="#jump-to-line" data-facebox-class="linejump" data-hotkey="l" class="hidden">Jump to Line</button>
<div id="jump-to-line" style="display:none">
  <!-- </textarea> --><!-- '"` --><form accept-charset="UTF-8" action="" class="js-jump-to-line-form" method="get"><div style="margin:0;padding:0;display:inline"><input name="utf8" type="hidden" value="&#x2713;" /></div>
    <input class="linejump-input js-jump-to-line-field" type="text" placeholder="Jump to line&hellip;" aria-label="Jump to line" autofocus>
    <button type="submit" class="btn">Go</button>
</form></div>

  </div>
  <div class="modal-backdrop"></div>
</div>


    </div>
  </div>

    </div>

        <div class="container site-footer-container">
  <div class="site-footer" role="contentinfo">
    <ul class="site-footer-links right">
        <li><a href="https://status.github.com/" data-ga-click="Footer, go to status, text:status">Status</a></li>
      <li><a href="https://developer.github.com" data-ga-click="Footer, go to api, text:api">API</a></li>
      <li><a href="https://training.github.com" data-ga-click="Footer, go to training, text:training">Training</a></li>
      <li><a href="https://shop.github.com" data-ga-click="Footer, go to shop, text:shop">Shop</a></li>
        <li><a href="https://github.com/blog" data-ga-click="Footer, go to blog, text:blog">Blog</a></li>
        <li><a href="https://github.com/about" data-ga-click="Footer, go to about, text:about">About</a></li>
          <li><a href="https://github.com/pricing" data-ga-click="Footer, go to pricing, text:pricing">Pricing</a></li>

    </ul>

    <a href="https://github.com" aria-label="Homepage" class="site-footer-mark">
      <svg aria-hidden="true" class="octicon octicon-mark-github" height="24" role="img" title="GitHub " version="1.1" viewBox="0 0 16 16" width="24"><path d="M8 0C3.58 0 0 3.58 0 8c0 3.54 2.29 6.53 5.47 7.59 0.4 0.07 0.55-0.17 0.55-0.38 0-0.19-0.01-0.82-0.01-1.49-2.01 0.37-2.53-0.49-2.69-0.94-0.09-0.23-0.48-0.94-0.82-1.13-0.28-0.15-0.68-0.52-0.01-0.53 0.63-0.01 1.08 0.58 1.23 0.82 0.72 1.21 1.87 0.87 2.33 0.66 0.07-0.52 0.28-0.87 0.51-1.07-1.78-0.2-3.64-0.89-3.64-3.95 0-0.87 0.31-1.59 0.82-2.15-0.08-0.2-0.36-1.02 0.08-2.12 0 0 0.67-0.21 2.2 0.82 0.64-0.18 1.32-0.27 2-0.27 0.68 0 1.36 0.09 2 0.27 1.53-1.04 2.2-0.82 2.2-0.82 0.44 1.1 0.16 1.92 0.08 2.12 0.51 0.56 0.82 1.27 0.82 2.15 0 3.07-1.87 3.75-3.65 3.95 0.29 0.25 0.54 0.73 0.54 1.48 0 1.07-0.01 1.93-0.01 2.2 0 0.21 0.15 0.46 0.55 0.38C13.71 14.53 16 11.53 16 8 16 3.58 12.42 0 8 0z"></path></svg>
</a>
    <ul class="site-footer-links">
      <li>&copy; 2016 <span title="0.06282s from github-fe128-cp1-prd.iad.github.net">GitHub</span>, Inc.</li>
        <li><a href="https://github.com/site/terms" data-ga-click="Footer, go to terms, text:terms">Terms</a></li>
        <li><a href="https://github.com/site/privacy" data-ga-click="Footer, go to privacy, text:privacy">Privacy</a></li>
        <li><a href="https://github.com/security" data-ga-click="Footer, go to security, text:security">Security</a></li>
        <li><a href="https://github.com/contact" data-ga-click="Footer, go to contact, text:contact">Contact</a></li>
        <li><a href="https://help.github.com" data-ga-click="Footer, go to help, text:help">Help</a></li>
    </ul>
  </div>
</div>



    
    
    

    <div id="ajax-error-message" class="ajax-error-message flash flash-error">
      <svg aria-hidden="true" class="octicon octicon-alert" height="16" role="img" version="1.1" viewBox="0 0 16 16" width="16"><path d="M15.72 12.5l-6.85-11.98C8.69 0.21 8.36 0.02 8 0.02s-0.69 0.19-0.87 0.5l-6.85 11.98c-0.18 0.31-0.18 0.69 0 1C0.47 13.81 0.8 14 1.15 14h13.7c0.36 0 0.69-0.19 0.86-0.5S15.89 12.81 15.72 12.5zM9 12H7V10h2V12zM9 9H7V5h2V9z"></path></svg>
      <button type="button" class="flash-close js-flash-close js-ajax-error-dismiss" aria-label="Dismiss error">
        <svg aria-hidden="true" class="octicon octicon-x" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M7.48 8l3.75 3.75-1.48 1.48-3.75-3.75-3.75 3.75-1.48-1.48 3.75-3.75L0.77 4.25l1.48-1.48 3.75 3.75 3.75-3.75 1.48 1.48-3.75 3.75z"></path></svg>
      </button>
      Something went wrong with that request. Please try again.
    </div>


      <script crossorigin="anonymous" src="https://assets-cdn.github.com/assets/compat-7db58f8b7b91111107fac755dd8b178fe7db0f209ced51fc339c446ad3f8da2b.js"></script>
      <script crossorigin="anonymous" src="https://assets-cdn.github.com/assets/frameworks-e677f2022a5d36e8f5ad35d0fcb01f83f1cdb613eda0449f533197693bcc6bda.js"></script>
      <script async="async" crossorigin="anonymous" src="https://assets-cdn.github.com/assets/github-49c0de53df0e1f0dfaa632dcbe0daafc2222a8021741cedf015685977e77c100.js"></script>
      
      
      
      
    <div class="js-stale-session-flash stale-session-flash flash flash-warn flash-banner hidden">
      <svg aria-hidden="true" class="octicon octicon-alert" height="16" role="img" version="1.1" viewBox="0 0 16 16" width="16"><path d="M15.72 12.5l-6.85-11.98C8.69 0.21 8.36 0.02 8 0.02s-0.69 0.19-0.87 0.5l-6.85 11.98c-0.18 0.31-0.18 0.69 0 1C0.47 13.81 0.8 14 1.15 14h13.7c0.36 0 0.69-0.19 0.86-0.5S15.89 12.81 15.72 12.5zM9 12H7V10h2V12zM9 9H7V5h2V9z"></path></svg>
      <span class="signed-in-tab-flash">You signed in with another tab or window. <a href="">Reload</a> to refresh your session.</span>
      <span class="signed-out-tab-flash">You signed out in another tab or window. <a href="">Reload</a> to refresh your session.</span>
    </div>
    <div class="facebox" id="facebox" style="display:none;">
  <div class="facebox-popup">
    <div class="facebox-content" role="dialog" aria-labelledby="facebox-header" aria-describedby="facebox-description">
    </div>
    <button type="button" class="facebox-close js-facebox-close" aria-label="Close modal">
      <svg aria-hidden="true" class="octicon octicon-x" height="16" role="img" version="1.1" viewBox="0 0 12 16" width="12"><path d="M7.48 8l3.75 3.75-1.48 1.48-3.75-3.75-3.75 3.75-1.48-1.48 3.75-3.75L0.77 4.25l1.48-1.48 3.75 3.75 3.75-3.75 1.48 1.48-3.75 3.75z"></path></svg>
    </button>
  </div>
</div>

  </body>
</html>

