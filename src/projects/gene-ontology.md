# Gene Ontology Database Search GUI

During a 2014 research internship at [Scripps Translational Science Institute](https://www.scripps.edu/science-and-medicine/translational-institute/), I worked under Dr. Ali Torkamani and completed two projects: a diagram of pharmaceutical drug pathways affecting a certain gene, and a Java 7 GUI application that searches a supplied gene ontology database for relevant results. This page describes that gene ontology database search application, which I created over the course of four days during the internship.

## Motivation

> Gene ontology (GO) is a major bioinformatics initiative to unify the representation of gene and gene product attributes across all species. More specifically, the project aims to: 1) maintain and develop its controlled vocabulary of gene and gene product attributes; 2) annotate genes and gene products, and assimilate and disseminate annotation data; and 3) provide tools for easy access to all aspects of the data provided by the project, and to enable functional interpretation of experimental data using the GO, for example via enrichment analysis.
>
> – [Wikipedia article on Gene Ontology](https://en.wikipedia.org/wiki/Gene_ontology)

Gene ontology relies on identifying associations between genes and gene symptoms. For this project, I was given a spreadsheet containing a sheet of unstandardized entries with genes/symptoms and a sheet of standardized entries, linking genes with symptoms, relevant terms, and corresponding scientific publications. The standardized entries had been previously curated by researchers, while the unstandardized entries had yet to be curated and added to standardized entries. Dr. Torkamani requested that I create a search indexing algorithm that, given an unstandardized entry, finds the most relevant standardized entries in the database.

![Standardized Data](/static/projects/gene-ontology/standardized-screen.png)
*Standardized data tab, showing comprehensive curated results.*

![Unstandardized Data](/static/projects/gene-ontology/unstandardized-screen.png)
*Unstandardized data to be matched with existing standardized data.*

## Solution

Towards this goal, Dr. Torkamani suggested a few text mining solutions, including a term frequency–inverse document frequency (tf-idf) algorithm.

> In information retrieval, tf–idf or TFIDF, short for term frequency–inverse document frequency, is a numerical statistic that is intended to reflect how important a word is to a document in a collection or corpus.[1] It is often used as a weighting factor in searches of information retrieval, text mining, and user modeling. The tf–idf value increases proportionally to the number of times a word appears in the document and is offset by the number of documents in the corpus that contain the word, which helps to adjust for the fact that some words appear more frequently in general.
>
> – [Wikipedia article on tf-idf](https://en.wikipedia.org/wiki/Tf%E2%80%93idf)

I implemented a tf-idf algorithm in Java which uses unstandardized entries' genes and symptoms as search terms and standardized entries as "documents" to be searched for relevant words. If the gene matches between an unstandardized and standardized entry, the relevance score increases by a static half point. To initiate a search, a user can select a row in the unstandardized entries sheet and press the search button, and the application populates the Search Results tabs with results ranked by relevance.

![Selecting an Entry](/static/projects/gene-ontology/select-entry.png)
*Selecting an entry: BRCA1 - breast cancer early on-set.*

![Search Results](/static/projects/gene-ontology/search-results.png)
*Search results ranked by relevance, shown in the first column.*

An additional requirement for this project was the ability to refine the search function by ignoring meaningless terms or adding synonyms to create consistent single terms for related words like cancer and carcinoma, or tumor and tumour. To incorporate these functionalities, I created a Settings tab with the ability to add ignored terms and synonyms, which are all saved to a local database file and persisted between sessions.

![Settings Page](/static/projects/gene-ontology/settings.png)
*Settings page, showing the built-in ignored terms and synonyms.*

## Assets

* [Project Code (Java)](/static/projects/gene-ontology/GeneOntology%20-%20Source.zip)
* [Precompiled Runnable JAR](/static/projects/gene-ontology/GeneOntology.jar)
* [Curation database spreadsheet (Excel)](/static/projects/gene-ontology/curation_inprogress.xlsm)