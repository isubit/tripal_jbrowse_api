<?php

const TRIPAL_JBROWSE_API_QUERY_ALL_ORGANISMS = <<<'EOQ'
    SELECT
        organism_id, genus, species, common_name
    FROM
        {organism} organism
EOQ;

const TRIPAL_JBROWSE_API_QUERY_ORGANISM_BY_COMMON_NAME = <<<'EOQ'
    SELECT
        organism_id, genus, species, common_name
    FROM
        {organism} organism
    WHERE
        common_name = :organism_common_name
EOQ;

const TRIPAL_JBROWSE_API_QUERY_SO_TYPE = <<<'EOQ'
    SELECT
        cvterm.name as type
    FROM
        {feature} feature, {cvterm} cvterm
    WHERE
        (feature.organism_id = :organism_id)
        AND
        feature.type_id = cvterm.cvterm_id
    GROUP BY
        cvterm.name
        ;

EOQ;

const TRIPAL_JBROWSE_API_QUERY_SIMPLE_FEATURE_QUERY_WITH_PARENT = <<<'EOQ'
    WITH RECURSIVE feature_tree(xfeature_id, feature_type, feature_fmin, feature_fmax, feature_strand, feature_name, feature_uniquename, object_id, parent_id)
    AS (
        SELECT
            feature.feature_id as xfeature_id,
            cvterm.name AS feature_type,
            featureloc.fmin AS feature_fmin,
            featureloc.fmax AS feature_fmax,
            featureloc.strand AS feature_strand,
            feature.name AS feature_name,
            feature.uniquename AS feature_uniquename,
            feature.feature_id as object_id,
            feature.feature_id as parent_id
        FROM {feature} feature
            LEFT JOIN
            {featureloc} featureloc ON (feature.feature_id = featureloc.feature_id)
            LEFT JOIN
            {cvterm} cvterm ON (feature.type_id = cvterm.cvterm_id)
        WHERE
            (feature.organism_id = :organism_id)
            AND
            /* with queried seqid */
            (featureloc.srcfeature_id IN (SELECT feature_id FROM {feature} WHERE uniquename = :refseq))
            AND
            /* within queried region */
            (featureloc.fmin <= :end AND :start <= featureloc.fmax)
            /* top level only */
            AND cvterm.name = :soType
    UNION ALL
        SELECT
            feature.feature_id as xfeature_id,
            cvterm.name AS feature_type,
            featureloc.fmin AS feature_fmin,
            featureloc.fmax AS feature_fmax,
            featureloc.strand AS feature_strand,
            feature.name AS feature_name,
            feature.uniquename AS feature_uniquename,
            feature.feature_id as object_id,
            feature_relationship.object_id as parent_id
        FROM {feature_relationship} feature_relationship
            LEFT JOIN
            feature ON (feature.feature_id = feature_relationship.subject_id
                        AND feature_relationship.type_id IN (SELECT cvterm_id FROM {cvterm} WHERE name = 'part_of'))
            LEFT JOIN
            featureloc ON (feature.feature_id = featureloc.feature_id)
            LEFT JOIN
            cvterm ON (feature.type_id = cvterm.cvterm_id)
            JOIN
            cvterm reltype ON (reltype.cvterm_id = feature_relationship.type_id),
            feature_tree
        WHERE
            feature_relationship.object_id = feature_tree.object_id
            AND feature_relationship.type_id IN (SELECT cvterm_id FROM {cvterm} WHERE name = 'part_of')
    )
    SELECT xfeature_id, feature_type, feature_fmin, feature_fmax, feature_strand, feature_name, feature_uniquename, parent_id FROM feature_tree;
EOQ;

const TRIPAL_JBROWSE_API_QUERY_REFSEQ = <<<'EOQ'
    SELECT
        seqlen, uniquename as name
    FROM
        {feature}
    WHERE
        organism_id = :organism_id
        AND
        type_id IN (select cvterm_id from {cvterm} cvterm join {cv} cv using (cv_id)
                    where cvterm.name = :sequence_type and cv.name = 'sequence')
    ;

EOQ;

const TRIPAL_JBROWSE_API_QUERY_REFSEQ_SEQ = <<<'EOQ'
    SELECT
        substring(residues, :start::int, :end::int) as seq
    FROM
        {feature} feature
    WHERE
        uniquename = :refseq
        AND
        feature.organism_id = :organism_id
        AND
        residues is not NULL
    ;
EOQ;
