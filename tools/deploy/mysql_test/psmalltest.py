# -*- coding: utf-8 -*-
psmall_test=[
"plan_cache.plan_cache_select_list",
"plan_cache.plan_cache_multi_query",
"window_function.farm",
"groupby.group_by_basic",
"global_index.global_index_select",
"inner_table.table_privileges",
"inner_table.views",
"inner_table.inner_table_overall",
"inner_table.user_privileges",
"inner_table.session_status",
"inner_table.all_virtual_sys_parameter_stat",
"inner_table.all_virtual_data_type",
"inner_table.all_virtual_upgrade_inspection",
"inner_table.tenant_virtual_statname",
"inner_table.global_variables",
"inner_table.schemata",
"inner_table.session_variables",
"inner_table.global_status",
"inner_table.table_constraints",
"inner_table.partitions",
"inner_table.all_virtual_data_type_class",
"inner_table.character_sets",
"inner_table.all_virtual_engine",
"meta_info.meta_func_floor",
"meta_info.meta_func_ceil",
"meta_info.meta_const",
"meta_info.meta_test_func_return_type",
"meta_info.meta_build_in_func_test",
"meta_info.meta_func",
"join.nested_loop_join_right_null_joinon",
"join.nested_loop_join_right_null",
"join.join_merge",
"join.nested_loop_join_right_null_joinon_where",
"join.anti_semi_join",
"hierarchical_query.hierarchical_basic_mysql",
"optimizer.union_sort_opt",
"optimizer.equal_set_mysql",
"optimizer.default_statistic",
"optimizer.estimate_cost",
"optimizer.bushy_leading_hint",
"subquery.order_by_subquery",
"subquery.subquery_sj_innodb",
"information_schema.information_schema_desc",
"executor.full_join",
"px.alloc_material_for_producer_consumer_schedule_mode",
#"px.join_nlj",
"px.join_mj",
"px.join_pwj",
"px.sql_audit",
"px.dml_use_px",
"px.add_material",
"px.default_open_px",
"trx.serializable_constrains",
"static_engine.expr_concat",
"static_engine.expr_todays",
"static_engine.expr_abs",
"static_engine.expr_substr",
"static_engine.expr_repeat",
"static_engine.expr_dump",
"static_engine.explicit_cast",
"static_engine.merge_set",
"static_engine.expr_nullif_ifnull",
"static_engine.expr_sys_privilege_check",
"static_engine.expr_nextval",
"static_engine.expr_get_sys_var",
"static_engine.expr_trunc",
"static_engine.expr_timestampadd",
"static_engine.expr_and_or",
"static_engine.px_basic",
"static_engine.expr_is_serving_tenant",
"static_engine.expr_lnnvl",
"static_engine.subplan_scan",
"static_engine.expr_str",
"static_engine.expr_unix_timestamp",
"static_engine.expr_bool",
"static_engine.expr_xor",
"static_engine.material",
"static_engine.expr_length",
"static_engine.expr_conv",
"static_engine.expr_lower_upper",
"static_engine.expr_regexp_func",
"static_engine.expr_time_diff",
"static_engine.expr_part_hash",
"static_engine.expr_field",
"static_engine.expr_replace",
"static_engine.expr_nvl",
"static_engine.static_engine_hash",
"static_engine.static_engine_cmp_null",
"static_engine.static_engine_case",
"static_engine.expr_trim",
"static_engine.expr_is",
"static_engine.expr_part_key",
"static_engine.expr_empty_arg",
"static_engine.subplan_filter",
"static_engine.expr_assign",
"static_engine.expr_pad",
"static_engine.expr_substring_index",
"static_engine.expr_get_user_var",
"static_engine.expr_regexp",
"static_engine.expr_char_length",
"static_engine.expr_sign",
"static_engine.expr_location",
"static_engine.table_insert",
"static_engine.expr_datediff",
"static_engine.table_scan",
"static_engine.expr_unhex",
"static_engine.expr_des_hex_str",
"static_engine.expr_date",
"static_engine.expr_collation",
"static_engine.expr_not",
"expr.func_regexp",
"expr.expr_instr",
"expr.func_length",
"expr.expr_floor",
"expr.expr_export_set",
"expr.expr_ceil",
"expr.expr_locate",
"expr.expr_nseq",
"expr.expr_convert_tz",
"expr.expr_position",
"expr.func_equal",
"expr.collation_expr",
"transformer.transformer_add_limit_for_union",
"transformer.transformer_predicate_deduce",
"type_date.test_select_usec_to_time",
"type_date.add_timestamp_column",
"type_date.daylight_saving_time",
"type_date.timefuncnull",
"type_date.type_create_time",
"type_date.updaterowkeymoditime",
"type_date.type_modify_time",
"type_date.expr_date_add_sub",
"type_date.datetime_java",
"alter.alter_log_archive_option",
"skyline.skyline_complicate_mysql",
"skyline.skyline_basic_mysql",
"with_clause_mysql.cte_without_explain_2_mysql",
"with_clause_mysql.basic_mysql",
"with_clause_mysql.cte_without_explain_mysql",
"with_clause_mysql.cte_mysql_official",
"with_clause_mysql.cte_errno_mysql",
"with_clause_mysql.recursive_optimize_mysql",
"with_clause_mysql.recursive_cycle_mysql",
"with_clause_mysql.recursive_mysql",
"with_clause_mysql.dis_recursive_mysql",
"with_clause_mysql.recursive_join_mysql",
"pl.pl_basic_mysql",
"pl.pl_dbt2_mysql",
"pl.pl_exception_basic_mysql",
"pl.pl_exception_mysql",
"pl.sp-bugs_mysql",
"pl.sp_mysql",
"pl.sp-vars_mysql",
"pl.sp-fib_mysql",
"type_date.add_timestamp_column",
"type_date.daylight_saving_time",
"type_date.timefuncnull",
"type_date.type_create_time",
"type_date.updaterowkeymoditime",
"type_date.type_modify_time",
"type_date.expr_date_add_sub",
"type_date.datetime_java",
"alter.alter_log_archive_option",
"skyline.skyline_complicate_mysql",
"skyline.skyline_basic_mysql",
"with_clause_mysql.cte_without_explain_2_mysql",
"with_clause_mysql.basic_mysql",
"with_clause_mysql.cte_without_explain_mysql",
"with_clause_mysql.cte_mysql_official",
"with_clause_mysql.cte_errno_mysql",
"with_clause_mysql.recursive_optimize_mysql",
"with_clause_mysql.recursive_cycle_mysql",
"with_clause_mysql.recursive_mysql",
"with_clause_mysql.dis_recursive_mysql",
"with_clause_mysql.recursive_join_mysql",
"pl.pl_basic_mysql",
"pl.pl_dbt2_mysql",
"pl.pl_exception_basic_mysql",
"pl.pl_exception_mysql",
"pl.sp-bugs_mysql",
"pl.sp_mysql",
#"pl.sp-vars_mysql",
"pl.sp-fib_mysql",
"geometry.geometry_basic_mysql"
]
