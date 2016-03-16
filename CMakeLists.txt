cmake_minimum_required(VERSION 2.8.7)
project(mosesdecoder)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# for KenLMFunctions.cmake
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(cmake/KenLMFunctions.cmake)


set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED COMPONENTS
  system
  thread
  filesystem
  unit_test_framework
  program_options
  iostreams
)

find_package(ZLIB REQUIRED)

# note: this one should only apply to a single source file. 
# moses/Parameter.cpp:460:16: error: ‘MOSES_VERSION_ID’ was not declared in this scope
# TODO: the others should NOT recompile when we have a new revision.
execute_process(COMMAND git describe --dirty OUTPUT_VARIABLE MOSES_VERSION_ID OUTPUT_STRIP_TRAILING_WHITESPACE)

# see also https://ccache.samba.org/

# TODO: these should be on the moses level, they should not affect kenlm, ideally...
add_definitions(-DMAX_NUM_FACTORS=4 -DKENLM_MAX_ORDER=6 -DWITH_THREADS -DBOOST_TEST_DYN_LINK -DPT_UG -DLM_IRST)
# -DMOSES_VERSION_ID="${MOSES_VERSION_ID}"

# TODO: make scope clear: name define PARAMETER_CPP_MOSES_VERSION_ID
set_source_files_properties(moses/Parameter.cpp PROPERTIES COMPILE_FLAGS -DMOSES_VERSION_ID=\\\"${MOSES_VERSION_ID}\\\")

# TODO: this should come from a find_package(irstlm)
# alas, IRSTLM does not define irstlm-config.cmake nor is there FindIRSTLM.cmake
# lazyness wins me this time.
#
# this points to the MMT/include folder now.
set(IRSTLM_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/../../include/")
set(IRSTLM_LIBRARIES "${CMAKE_SOURCE_DIR}/../../lib/libirstlm.so")

# . is for #include<moses/...> style includes
include_directories(${Boost_INCLUDE_DIRS} ${IRSTLM_INCLUDE_DIRS} .)

# KenLM
add_subdirectory(util)
add_subdirectory(lm)

set(MOSES_SRC
moses/AlignmentInfoCollection.cpp
moses/AlignmentInfo.cpp
moses/BaseManager.cpp
moses/BitmapContainer.cpp
moses/Bitmap.cpp
moses/Bitmaps.cpp
moses/ChartCellCollection.cpp
moses/ChartCell.cpp
moses/ChartHypothesisCollection.cpp
moses/ChartHypothesis.cpp
moses/ChartKBestExtractor.cpp
moses/ChartManager.cpp
moses/ChartParser.cpp
moses/ChartRuleLookupManager.cpp
moses/ChartTranslationOption.cpp
moses/ChartTranslationOptionList.cpp
moses/ChartTranslationOptions.cpp
moses-cmd/Main.cpp
moses/ConfusionNet.cpp
moses/DecodeGraph.cpp
moses/DecodeStep.cpp
moses/DecodeStepGeneration.cpp
moses/DecodeStepTranslation.cpp
moses/ExportInterface.cpp
moses/FactorCollection.cpp
moses/Factor.cpp
moses/FactorTypeSet.cpp
moses/FeatureVector.cpp
#moses/FF/BleuScoreFeature.cpp
#moses/FF/ConstrainedDecoding.cpp
#moses/FF/ControlRecombination.cpp
#moses/FF/CountNonTerms.cpp
#moses/FF/CoveredReferenceFeature.cpp
moses/FF/DecodeFeature.cpp
#moses/FF/DeleteRules.cpp
moses/FF/DistortionScoreProducer.cpp
moses/FF/DynamicCacheBasedLanguageModel.cpp
#moses/FF/Factory.cpp
moses/FF/FeatureFunction.cpp
moses/FF/FFState.cpp
#moses/FF/GlobalLexicalModel.cpp
#moses/FF/GlobalLexicalModelUnlimited.cpp
#moses/FF/HyperParameterAsWeight.cpp
moses/FF/InputFeature.cpp
moses/FF/InternalTree.cpp
moses/FF/LexicalReordering/LexicalReordering.cpp
moses/FF/LexicalReordering/LexicalReorderingState.cpp
moses/FF/LexicalReordering/LexicalReorderingTable.cpp
moses/FF/LexicalReordering/ReorderingStack.cpp
moses/FF/LexicalReordering/SparseReordering.cpp
#moses/FF/MaxSpanFreeNonTermSource.cpp
#moses/FF/Model1Feature.cpp
#moses/FF/NieceTerminal.cpp
#moses/FF/OSM-Feature/KenOSM.cpp
#moses/FF/OSM-Feature/OpSequenceModel.cpp
#moses/FF/OSM-Feature/osmHyp.cpp
#moses/FF/PhraseBoundaryFeature.cpp
#moses/FF/PhraseLengthFeature.cpp
#moses/FF/PhraseOrientationFeature.cpp
#moses/FF/PhrasePairFeature.cpp
moses/FF/PhrasePenalty.cpp
#moses/FF/ReferenceComparison.cpp
#moses/FF/RulePairUnlexicalizedSource.cpp
#moses/FF/RuleScope.cpp
#moses/FF/SetSourcePhrase.cpp
moses/FF/SkeletonStatefulFF.cpp
moses/FF/SkeletonStatelessFF.cpp
#moses/FF/SoftMatchingFeature.cpp
#moses/FF/SoftSourceSyntacticConstraintsFeature.cpp
#moses/FF/SourceGHKMTreeInputMatchFeature.cpp
#moses/FF/SourceWordDeletionFeature.cpp
#moses/FF/SpanLength.cpp
#moses/FF/SparseHieroReorderingFeature.cpp
moses/FF/StatefulFeatureFunction.cpp
moses/FF/StatelessFeatureFunction.cpp
#moses/FF/SyntaxRHS.cpp
#moses/FF/TargetBigramFeature.cpp
#moses/FF/TargetConstituentAdjacencyFeature.cpp
#moses/FF/TargetNgramFeature.cpp
#moses/FF/TargetPreferencesFeature.cpp
#moses/FF/TargetWordInsertionFeature.cpp
#moses/FF/TreeStructureFeature.cpp
#moses/FF/UnalignedWordCountFeature.cpp
moses/FF/UnknownWordPenaltyProducer.cpp
moses/FF/WordPenaltyProducer.cpp
#moses/FF/WordTranslationFeature.cpp
moses/File.cpp
moses/FloydWarshall.cpp
moses/GenerationDictionary.cpp
moses/HypergraphOutput.cpp
moses/Hypothesis.cpp
moses/HypothesisStack.cpp
moses/HypothesisStackCubePruning.cpp
moses/HypothesisStackNormal.cpp
moses/Incremental.cpp
moses/InputFileStream.cpp
moses/InputPath.cpp
moses/InputType.cpp
#moses/IOWrapper.cpp
moses/LatticeMBR.cpp
moses/LM/Backward.cpp
moses/LM/BackwardLMState.cpp
moses/LM/Base.cpp
moses/LM/BilingualLM.cpp
moses/LM/Implementation.cpp
moses/LM/IRST.cpp
moses/LM/Ken.cpp
moses/LM/MultiFactor.cpp
moses/LM/Remote.cpp
moses/LM/SingleFactor.cpp
moses/LM/SkeletonLM.cpp
moses/LVoc.cpp
moses/Manager.cpp
moses/mbr.cpp
moses/NonTerminal.cpp
moses/OutputFileStream.cpp
moses/Parameter.cpp
moses/parameters/AllOptions.cpp
moses/parameters/BookkeepingOptions.cpp
moses/parameters/ContextParameters.cpp
moses/parameters/CubePruningOptions.cpp
moses/parameters/InputOptions.cpp
moses/parameters/LMBR_Options.cpp
moses/parameters/MBR_Options.cpp
moses/parameters/NBestOptions.cpp
moses/parameters/OOVHandlingOptions.cpp
moses/parameters/OptionsBaseClass.cpp
moses/parameters/ReorderingOptions.cpp
moses/parameters/ReportingOptions.cpp
moses/parameters/SearchOptions.cpp
moses/parameters/ServerOptions.cpp
moses/parameters/SyntaxOptions.cpp
moses/PartialTranslOptColl.cpp
moses/PCNTools.cpp
moses/Phrase.cpp
moses/PP/CountsPhraseProperty.cpp
moses/PP/Factory.cpp
moses/PP/NonTermContextProperty.cpp
moses/PP/OrientationPhraseProperty.cpp
moses/PP/PhraseProperty.cpp
moses/PP/SourceLabelsPhraseProperty.cpp
moses/PP/SpanLengthPhraseProperty.cpp
moses/PP/TargetConstituentBoundariesLeftPhraseProperty.cpp
moses/PP/TargetConstituentBoundariesRightAdjacentPhraseProperty.cpp
moses/PP/TargetPreferencesPhraseProperty.cpp
moses/PrefixTreeMap.cpp
moses/Range.cpp
moses/ReorderingConstraint.cpp
moses/RuleCube.cpp
moses/RuleCubeItem.cpp
moses/RuleCubeQueue.cpp
moses/ScoreComponentCollection.cpp
moses/Search.cpp
moses/SearchCubePruning.cpp
moses/SearchNormal.cpp
moses/Sentence.cpp
moses/SentenceStats.cpp
moses/SquareMatrix.cpp
moses/StaticData.cpp
moses/TabbedSentence.cpp
moses/TargetPhraseCollection.cpp
moses/TargetPhrase.cpp
moses/ThreadPool.cpp
moses/Timer.cpp
moses/TranslationAnalysis.cpp
moses/TranslationModel/PhraseDictionary.cpp
moses/TranslationModel/PhraseDictionaryDynamicCacheBased.cpp ## rather not :/
moses/TranslationModel/PhraseDictionaryTree.cpp # meh.
moses/TranslationModel/PhraseDictionaryTreeAdaptor.cpp # meh.
moses/PDTAimp.cpp # meh.
moses/TranslationModel/UG/generic/file_io/ug_stream.cpp
moses/TranslationModel/UG/generic/program_options/ug_get_options.cpp
moses/TranslationModel/UG/generic/program_options/ug_splice_arglist.cc
moses/TranslationModel/UG/generic/threading/ug_thread_pool.cc
moses/TranslationModel/UG/generic/threading/ug_thread_safe_counter.cc
moses/TranslationModel/UG/mm/num_read_write.cc
moses/TranslationModel/UG/mmsapt_align.cc
moses/TranslationModel/UG/mmsapt.cpp
moses/TranslationModel/UG/mm/tpt_pickler.cc
moses/TranslationModel/UG/mm/tpt_tightindex.cc
moses/TranslationModel/UG/mm/tpt_tokenindex.cc
moses/TranslationModel/UG/mm/ug_bitext.cc
moses/TranslationModel/UG/mm/ug_bitext_jstats.cc
moses/TranslationModel/UG/mm/ug_bitext_pstats.cc
moses/TranslationModel/UG/mm/ug_bitext_sampler.cc
moses/TranslationModel/UG/mm/ug_conll_record.cc
moses/TranslationModel/UG/mm/ug_corpus_token.cc
moses/TranslationModel/UG/mm/ug_deptree.cc
moses/TranslationModel/UG/mm/ug_http_client.cc
moses/TranslationModel/UG/mm/ug_im_bitext.cc
moses/TranslationModel/UG/mm/ug_lexical_reordering.cc
moses/TranslationModel/UG/mm/ug_load_primer.cc
moses/TranslationModel/UG/mm/ug_phrasepair.cc
moses/TranslationModel/UG/mm/ug_sampling_bias.cc
moses/TranslationModel/UG/mm/ug_tsa_array_entry.cc
moses/TranslationModel/UG/mm/ug_ttrack_base.cc
moses/TranslationModel/UG/mm/ug_ttrack_position.cc
moses/TranslationModel/UG/TargetPhraseCollectionCache.cc
moses/TranslationOptionCollectionConfusionNet.cpp
moses/TranslationOptionCollection.cpp
moses/TranslationOptionCollectionLattice.cpp
moses/TranslationOptionCollectionText.cpp
moses/TranslationOption.cpp
moses/TranslationOptionList.cpp
#moses/TranslationTask.cpp
moses/TreeInput.cpp
moses/TrellisPathCollection.cpp
moses/TrellisPath.cpp
moses/Util.cpp
moses/Word.cpp
moses/WordLattice.cpp
moses/XmlOption.cpp
#OnDiskPt/OnDiskQuery.cpp
#OnDiskPt/OnDiskWrapper.cpp
#OnDiskPt/Phrase.cpp
#OnDiskPt/PhraseNode.cpp
#OnDiskPt/SourcePhrase.cpp
#OnDiskPt/TargetPhraseCollection.cpp
#OnDiskPt/TargetPhrase.cpp
#OnDiskPt/Vocab.cpp
#OnDiskPt/Word.cpp
phrase-extract/PhraseOrientation.cpp
search/edge_generator.cc
search/nbest.cc
search/rule.cc
search/vertex.cc

# MMT specific: disable syntax decoding, unused phrase tables, unused features
contrib/other-builds/mmt/FF/Factory.cpp
contrib/other-builds/mmt/IOWrapper.cpp
contrib/other-builds/mmt/TranslationTask.cpp
)

# to do: above source files should be mentioned in their subdirectories.
# and then, e.g., add_subdirectory(TranslationModel/UG), ...



add_executable(moses ${MOSES_SRC} $<TARGET_OBJECTS:kenlm> $<TARGET_OBJECTS:kenlm_util>)
target_link_libraries(moses ${Boost_LIBRARIES} ${ZLIB_LIBRARIES} ${IRSTLM_LIBRARIES} pthread)


